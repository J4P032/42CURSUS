/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:32:40 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/23 17:00:49 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"


static bool	in_quotes(const char *str, int pos)
{
	char quote = 0;

	int i;
	i = 0;
	while (i < pos)
	{
		if ((str[i] == '\'' || str[i] == '\"'))
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		i++;
	}
	return (quote != 0);
}

char	**ft_split_pipes(const char *input)
{
	char	**result;
	int		count = 1;
	int		start = 0, end = 0, res_i = 0;

	int i;
	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && !in_quotes(input, i))
			count++;
		i++;
	}
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && !in_quotes(input, i))
		{
			end = i;
			result[res_i++] = strndup(input + start, end - start);
			start = i + 1;
		}
		i++;
	}
	result[res_i++] = strndup(input + start, strlen(input) - start);
	result[res_i] = NULL;
	return (result);
}

void	ft_manage_pipes(t_input *input)
{
	char	**commands;
	int		i = 0;
	int		pipefd[2];
	int		in_fd = STDIN_FILENO;
	pid_t	pid;

	// Divide el input por '|'
	commands = ft_split_pipes(input->parsed); // Esta función la tienes que hacer
	while (commands[i])
	{
		if (commands[i + 1])
			pipe(pipefd); // Crea un nuevo pipe

		pid = fork();
		if (pid == 0)
		{
			// Redirige stdin
			dup2(in_fd, STDIN_FILENO);
			if (commands[i + 1])
				dup2(pipefd[1], STDOUT_FILENO); // Redirige stdout al pipe

			// Cierra los pipes que no se usan
			if (commands[i + 1])
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			// Prepara el input->parsed o input->command para este comando
			t_input temp = *input; // Copia original
			temp.parsed = commands[i];
			temp.input_split = ft_split_quotes(temp.parsed, ' ', &temp);
			compose_command_args(&temp);
			parsing(&temp);
			ft_manage_input(&temp);
			exit(0); // Termina el hijo
		}
		else
		{
			waitpid(pid, NULL, 0);
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			if (commands[i + 1])
			{
				close(pipefd[1]);
				in_fd = pipefd[0]; // El input para el próximo comando
			}
		}
		i++;
	}
	ft_matrix_free(&commands);
}
