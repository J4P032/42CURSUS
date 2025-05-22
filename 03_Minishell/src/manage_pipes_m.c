/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:32:40 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/22 18:28:39 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	ft_manage_pipes(t_input *input)
{
	char	**cmds;
	int		pipefd[2];
	int		in_fd;
	int		i;
	pid_t	pid;
	int		status;
	t_input	sub_input;
	int		sig; //señales de javi

	i = 0;
	in_fd = 0;
	if (!ft_strchr_quotes(input->input, '|'))
	{
		ft_manage_input(input, STDIN_FILENO, STDOUT_FILENO);
		return ;
	}

	cmds = ft_split_quotes(input->input, '|', input);
	if (!cmds)
		return ;

	while (cmds[i])
	{
		if (cmds[i + 1] != NULL && pipe(pipefd) == -1)
		{
			perror("pipe");
			break ;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			break ;
		}

		if (pid == 0)
		{
			// ====== SEÑALES DE JAVI ======

			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);

			// =============================
			
			if (in_fd != 0)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (cmds[i + 1] != NULL)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			// ====== MANEJO DE SUB_INPUT CORRECTO ======
			ft_bzero(&sub_input, sizeof(t_input)); // limpia struct
			sub_input.input = ft_strtrim(cmds[i], " ");
			sub_input.envp = input->envp;
			ft_manage_input(&sub_input, STDIN_FILENO, STDOUT_FILENO);
			free(sub_input.input); // libera sub_input.input
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);

			// ====== SEÑALES DE JAVI ======
			
			if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGINT)
					write(1, "\n", 1);
				else if (sig == SIGQUIT)
					write(1, "Quit (core dumped)\n", 19);
				input->last_exit_code = 128 + sig;//128 es el codigo de terminacion por señal. Todas empiezan desde ahi. Por eso la suma. SIGINT (controlC = 2 asi que 130) y SIGQUIT (cont\ 3 -> 131)
			}

			// =============================

			if (cmds[i + 1] == NULL)
			{
				if (WIFEXITED(status))
					input->last_exit_code = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					input->last_exit_code = 128 + WTERMSIG(status);
				else
					input->last_exit_code = 1;
			}

			if (in_fd != 0)
				close(in_fd);
			if (cmds[i + 1] != NULL)
			{
				close(pipefd[1]);
				in_fd = pipefd[0];
			}
		}
		i++;
	}

	ft_matrix_free(&cmds); // libera cmds generado por ft_split_quotes
}
