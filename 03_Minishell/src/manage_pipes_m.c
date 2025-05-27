/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:32:40 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/27 14:26:22 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

char **ft_subarray(char **array, int start, int end)
{
	int		len = end - start;
	char	**new_array = malloc(sizeof(char *) * (len + 1));
	int		i = 0;

	if (!new_array)
		return (NULL);
	while (start < end && array[start])
	{
		new_array[i] = ft_strdup(array[start]);
		if (!new_array[i])
		{
			// En caso de error, liberar lo ya duplicado
			while (--i >= 0)
				free(new_array[i]);
			free(new_array);
			return (NULL);
		}
		i++;
		start++;
	}
	new_array[i] = NULL;
	return (new_array);
}
void	copy_input_partial(t_input *src, t_input *dest)
{
	dest->envp = ft_matrix_dup(src->envp); // Asegúrate de tener esta función
	dest->last_exit_code = src->last_exit_code;
	dest->is_script = src->is_script;

	dest->input = NULL;
	dest->input_split = NULL;
	dest->parsed = NULL;
	dest->command = NULL;
	dest->args = NULL;
	dest->split_exp = NULL;

	dest->inputfd = STDIN_FILENO;
	dest->outputfd = STDOUT_FILENO;
}




void	ft_manage_pipes(t_input *input)
{
	int		num_cmds = 1;
	int		num_pipes = 0;
	int		i = 0;

	// Contar comandos separados por pipes reales
	while (input->split_exp[i])
	{
		if (ft_strcmp(input->split_exp[i], "|") == 0 && input->status_exp[i] == 0)
			num_cmds++;
		i++;
	}
	num_pipes = num_cmds - 1;

	int		pipefd[num_pipes][2];
	pid_t	pids[num_cmds];

	// Crear pipes
	for (int i = 0; i < num_pipes; i++)
		if (pipe(pipefd[i]) == -1)
			perror("pipe");

	// Ejecutar cada comando
	int start = 0;
	for (int cmd = 0; cmd < num_cmds; cmd++)
	{
		// Encontrar el fin del comando actual
		int end = start;
		while (input->split_exp[end] &&
			!(ft_strcmp(input->split_exp[end], "|") == 0 && input->status_exp[end] == 0))
			end++;

		// Crear nuevo input para el subcomando
		t_input sub_input;
		copy_input_partial(input, &sub_input); // Debes implementar esto para copiar solo los necesarios
		sub_input.input_split = ft_subarray(input->split_exp, start, end); // Igual, debes implementar esto
		compose_command_args(&sub_input);
		parsing(&sub_input);

		pids[cmd] = fork();
		if (pids[cmd] == 0)
		{
			// Redirecciones pipe
			if (cmd > 0)
			{
				dup2(pipefd[cmd - 1][0], STDIN_FILENO);
			}
			if (cmd < num_cmds - 1)
			{
				dup2(pipefd[cmd][1], STDOUT_FILENO);
			}
			// Cerrar todos los pipes en hijo
			for (int k = 0; k < num_pipes; k++)
			{
				close(pipefd[k][0]);
				close(pipefd[k][1]);
			}
			ft_manage_input(&sub_input);
			clean_all(&sub_input, 0);
			exit(0); // O exit(sub_input.last_exit_code);
		}
		// Liberar subinput si hace falta
		ft_input_free(&sub_input);

		start = end + 1;
	}

	// Cerrar todos los pipes en el padre
	for (int i = 0; i < num_pipes; i++)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}

	// Esperar a todos los hijos
	for (int i = 0; i < num_cmds; i++)
	{
		int status;
		waitpid(pids[i], &status, 0);
		if (i == num_cmds - 1) // Último comando define el exit status
			input->last_exit_code = WEXITSTATUS(status);
	}
}
