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
	while (input->input_split[i])
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

void	execute_pipeline(t_input *input)
{
	int		num_cmds;
	int		prev_fd;
	int		cmd_start;
	int		cmd;
	pid_t	last_pid;
	pid_t	pid;
	int		pipefd[2];
	int		i;
	int		k;
	int		cmd_end;
	int		argc;
	char	**args;
	t_input	*input_child;
	int		status;
	pid_t	wpid;
	int		sig; // señales NOOOO BORRAR

	num_cmds = input->total_pipes + 1;
	prev_fd = -1;
	cmd_start = 0;
	last_pid = -1;
	for (cmd = 0; cmd < num_cmds; cmd++)
	{
		cmd_end = cmd_start;
		while (input->split_exp[cmd_end] && !(ft_strcmp(input->split_exp[cmd_end], "|") == 0 && input->status_exp[cmd_end] == 0))
			cmd_end++;
		argc = cmd_end - cmd_start;
		args = malloc(sizeof(char *) * (argc + 1));
		if (!args)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < argc; i++)
			args[i] = ft_strdup(input->split_exp[cmd_start + i]);
		args[i] = NULL;
		if (cmd < num_cmds - 1)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			// ====== SEÑALES DE JAVI ======

			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);

			// =============================
			
			
			
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmd < num_cmds - 1)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			input_child = malloc(sizeof(t_input));
			init_input_struct(input_child);
			input_child->input = join_command(input->split_exp, cmd_start, cmd_end);
			input_child->input_split = ft_split_quotes(input_child->input, ' ', input_child);
			input_child->envp = input->envp;
			input_child->total_pipes = input->total_pipes;
			compose_command_args(input_child);
			free(input_child->filename);
			ft_compose_parsed(input_child);
			input_child->split_exp = ft_matrix_dup(input_child->input_split);
			for (k = 0; input_child->split_exp[k]; k++)
				input_child->status_exp[k] = input->status_exp[cmd_start + k];
			ft_manage_input(input_child);
			ft_input_free(input_child);
			for (i = 0; args[i]; i++)
				free(args[i]);
			free(args);
			exit(input_child->last_exit_code);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd < num_cmds - 1)
			{
				close(pipefd[1]);
				prev_fd = pipefd[0];
			}
			for (i = 0; args[i]; i++)
				free(args[i]);
			free(args);
			last_pid = pid;
		}
		cmd_start = cmd_end + 1;
	}
	while ((wpid = wait(&status)) > 0)
	{
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				input->last_exit_code = WEXITSTATUS(status);
			
			//SEÑALES!! NO BORRAR!!!
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
