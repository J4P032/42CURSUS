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

char	*join_command(char **split_exp, int start, int end)
{
	int		i;
	size_t	len;
	char	*joined;

	len = 0;
	i = start;
	while (i < end)
		len += ft_strlen(split_exp[i++]) + 1;
	joined = malloc(len + 1);
	if (!joined)
		return (NULL);
	joined[0] = '\0';
	i = start;
	while (i < end)
	{
		ft_strcat(joined, split_exp[i]);
		if (i < end - 1)
			ft_strcat(joined, " ");
		i++;
	}
	return (joined);
}

int	count_pipes(t_input *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input->split_exp && input->split_exp[i])
	{
		if (ft_strcmp(input->split_exp[i], "|") == 0
			&& input->status_exp[i] == 0)
			count++;
		i++;
	}
	return (count);
}

void	ft_compose_parsed(t_input *input)
{
	int		i;
	bool	first;

	i = 0;
	first = true;
	input->parsed = ft_strdup("");
	while (input->input_split && input->input_split[i])
	{
		if (ft_strcmp(input->input_split[i], input->command) == 0)
		{
			i++;
			continue ;
		}
		if (!first)
			input->parsed = ft_strjoin_r(input->parsed, " ");
		input->parsed = ft_strjoin_r(input->parsed, input->input_split[i]);
		first = false;
		i++;
	}
	input->parsed = ft_strjoin_r(input->parsed, "\0");
}

static char	**get_command_args(char **split_exp, int start, int end)
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

void	child_p(int prev_fd, int *pipefd, t_input *input, int cmd_start, int cmd_end)
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
	child_p_2(input, child, cmd_start, cmd_end);
	ft_manage_input(child);
	ft_input_free(child);
	exit(child->last_exit_code);
}

static void	handle_parent_process(int *prev_fd, int *pipefd, int is_last, char **args)
{
	int	i;

	if (*prev_fd != -1)
		close(*prev_fd);
	if (!is_last)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}

static void	wait_for_children(pid_t last_pid, t_input *input)
{
	int		status;
	pid_t	wpid;
	int		sig;

	while ((wpid = wait(&status)) > 0)
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
	}
}

void	execute_pipeline(t_input *input)
{
	int		num_cmds = input->total_pipes + 1;
	int		prev_fd = -1;
	int		cmd_start = 0;
	int		cmd, cmd_end;
	char	**args;
	int		pipefd[2];
	pid_t	pid, last_pid = -1;

	for (cmd = 0; cmd < num_cmds; cmd++)
	{
		cmd_end = cmd_start;
		while (input->split_exp[cmd_end] &&
			!(ft_strcmp(input->split_exp[cmd_end], "|") == 0 && input->status_exp[cmd_end] == 0))
			cmd_end++;
		args = get_command_args(input->split_exp, cmd_start, cmd_end);
		if (cmd < num_cmds - 1 && pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			child_p(prev_fd, (cmd < num_cmds - 1) ? pipefd : NULL, input, cmd_start, cmd_end);
		else
		{
			handle_parent_process(&prev_fd, pipefd, cmd == num_cmds - 1, args);
			last_pid = pid;
		}
		cmd_start = cmd_end + 1;
	}
	wait_for_children(last_pid, input);
}

void	ft_manage_pipes(t_input *input)
{
	input->inputfd = STDIN_FILENO;
	input->outputfd = STDOUT_FILENO;
	input->total_pipes = count_pipes(input);
	if (input->total_pipes == 0)
		ft_manage_input(input);
	else
		execute_pipeline(input);
	if (input)
		ft_input_free(input);
}
