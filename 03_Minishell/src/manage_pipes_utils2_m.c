/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:32:40 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/30 01:28:06 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

char	**get_command_args(char **split_exp, int start, int end)
{
	int		argc;
	char	**args;
	int		i;

	i = 0;
	argc = end - start;
	args = malloc(sizeof(char *) * (argc + 1));
	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (i < argc)
	{
		args[i] = ft_strdup(split_exp[start + i]);
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	child_p_2(t_input *input, t_input *child, int cmd_start, int cmd_end)
{
	int		k;

	k = 0;
	init_input_struct(child);
	child->input = join_command(input->split_exp, cmd_start, cmd_end);
	child->input_split = ft_split_quotes(child->input, ' ', child);
	child->envp = input->envp;
	child->total_pipes = input->total_pipes;
	compose_command_args(child);
	free(child->filename);
	ft_compose_parsed(child);
	child->split_exp = ft_matrix_dup(child->input_split);
	while (child->split_exp[k])
	{
		child->status_exp[k] = input->status_exp[cmd_start + k];
		k++;
	}
}

void	child_p(int prev_fd, int *pipefd, t_input *input)
{
	t_input	*child;

	child = malloc(sizeof(t_input));
	if (!child)
		exit(EXIT_FAILURE);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (pipefd)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	child_p_2(input, child, input->cmd_start, input->cmd_end);
	ft_manage_input(child);
	ft_input_free(child);
	exit(child->last_exit_code);
}

void	parent_p(int *prev_fd, int *pipefd, int is_last, char **args)
{
	int	i;

	i = 0;
	if (*prev_fd != -1)
		close(*prev_fd);
	if (!is_last)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	while (args[i])
		free(args[i++]);
	free(args);
}

void	wait_for_children(pid_t last_pid, t_input *input)
{
	int		status;
	pid_t	wpid;
	int		sig;

	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				input->last_exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGINT)
					write(1, "\n", 1);
				else if (sig == SIGQUIT)
					write(1, "Quit (core dumped)\n", 19);
				input->last_exit_code = 128 + sig;
			}
		}
		wpid = wait(&status);
	}
}
