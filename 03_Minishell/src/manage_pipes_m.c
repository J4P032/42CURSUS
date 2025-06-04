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

static char	**get_args_for_cmd(t_input *input)
{
	char	**args;

	input->cmd_end = input->cmd_start;
	if (input->cmd_end > 99)
	{
		perror("get_args_for_cmd: Force Exit. Too many arguments");
		clean_all(input, 1);
	}
	while (input->split_exp && input->split_exp[input->cmd_end]
		&& !(ft_strcmp(input->split_exp[input->cmd_end], "|") == 0
			&& input->status_exp[input->cmd_end] == 0))
		input->cmd_end++;
	args = get_command_args(input->split_exp,
			input->cmd_start, input->cmd_end);
	return (args);
}

pid_t	execute_pipeline_in(t_input *input, pid_t last_pid, int *prev_fd)
{
	int		pipefd[2];
	char	**args;
	pid_t	pid;

	args = get_args_for_cmd(input);
	setup_pipe(pipefd, input->cmd, input->num_cmds);
	pid = fork();
	if (pid == -1)
		handle_fork_error();
	if (pid == 0 && input->cmd < input->num_cmds - 1)
		child_p(*prev_fd, pipefd, input);
	else if (pid == 0)
		child_p(*prev_fd, NULL, input);
	else
	{
		parent_p(prev_fd, pipefd, input->cmd == input->num_cmds - 1, args);
		last_pid = pid;
	}
	input->cmd_start = input->cmd_end + 1;
	input->cmd++;
	if (last_pid)
		return (last_pid);
	return (0);
}

void	execute_pipeline(t_input *input)
{
	pid_t	last_pid;
	pid_t	last_pid2;
	int		prev_fd;

	last_pid2 = 0;
	prev_fd = -1;
	input->cmd = 0;
	input->num_cmds = input->total_pipes + 1;
	while (input->cmd < input->num_cmds)
		last_pid = execute_pipeline_in(input, last_pid2, &prev_fd);
	wait_for_children(last_pid, input);
}

void	ft_manage_pipes(t_input *input)
{
	struct sigaction	sa;

	input->inputfd = STDIN_FILENO;
	input->outputfd = STDOUT_FILENO;
	input->total_pipes = count_pipes(input);
	if (input->total_pipes == 0)
		ft_manage_input(input);
	else
	{
		signal(SIGQUIT, SIG_IGN);
		init_sigaction(&sa);
		execute_pipeline(input);
	}
	if (input)
		ft_input_free(input);
}
