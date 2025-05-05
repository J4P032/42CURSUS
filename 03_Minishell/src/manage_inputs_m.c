/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_inputs_m.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:28:00 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/05 19:17:59 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	compose_args(t_input *in, size_t word)
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		exit_while;
	int		status_done;

	k = 0;
	i = word;
	exit_while = 0;
	status_done = 0;
	ft_bzero(in->args, 100);
	while (i < in->input_words)
	{
		j = 0;
		status_done = 0;
		if (i > word && in->input_split[i][0] == '\0' 
			&& (in->status[i] == SQUO_SP || in->status[i] == DQUO_SP))
			break ;
		while ((in->input_split[i][j] != ' ' || is_quoted(in, i))
			&& in->input_split[i][j] != '\0' && !exit_while)
		{
			if ((i > word && (in->status[i] == EPTY_SP
				|| in->status[i] == SQUO_SP || in->status[i] == DQUO_SP)
				&& !status_done))
					exit_while = 1;
			else
				in->args[k++] = in->input_split[i][j++];
			status_done = 1;
		}
		if (in->input_split[i][j] == ' ' || exit_while)
			break ;
		i++;
	}
	in->word_after_arg = i;
}

void	compose_command_args(t_input *in)
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		exit_while;
	int		status_done;
	
	i = 0;
	k = 0;
	exit_while = 0;
	status_done = 0;
	ft_bzero(in->command, 250);
	while (i < in->input_words)
	{
		j = 0;
		status_done = 0;
		if (i > 0 && in->input_split[i][0] == '\0' && (in->status[i] == SQUO_SP
			|| in->status[i] == DQUO_SP))
			break ;
		while ((in->input_split[i][j] != ' ' || is_quoted(in, i))
			&& (in->input_split[i][j] != '\0') && !exit_while)
		{
			if (i > 0 && (in->status[i] == EPTY_SP
				|| in->status[i] == SQUO_SP || in->status[i] == DQUO_SP)
				&& !status_done)
				exit_while = 1;
			else
				in->command[k++] = in->input_split[i][j++];
			status_done = 1;
		}
		if (in->input_split[i][j] == ' ' || exit_while)
			break ;
		i++;
	}
	in->word_after_command = i;
	compose_args(in, i);
}


void	ft_manage_input(t_input *input, int in_fd, int out_fd)
{
	input->input_split = ft_split_quotes(input->input, ' ', input);
	input->inputfd = in_fd;
	input->outputfd = out_fd;
	if (!input->input_split || !input->input_split[0])
		return ;
	compose_command_args(input);
	//printf("command :%s\n", input->command);//
	//printf("arg :%s\n-------------\n", input->args);//
	if (ft_strcmp(input->input_split[0], "pwd") == 0)
		ft_pwd(input->input_split);
	else if (ft_strcmp(input->input_split[0], "cd") == 0)
		ft_cd(input->input_split, input->envp);
	else if (ft_strcmp(input->command, "echo") == 0)
		ft_echo(input);
	else if (ft_strcmp(input->input_split[0], "export") == 0
		&& input->input_split[1])
		ft_export(input->input_split[1], &input->envp);
	else if (ft_strcmp(input->input_split[0], "env") == 0)
		ft_env(input->input_split, input->envp);
	else if (ft_strcmp(input->input_split[0], "unset") == 0
		&& input->input_split[1])
		ft_unset(input->input_split[1], &input->envp);
	else 
		execute_command(input);
	ft_input_free(input);
}

void	ft_manage_pipes(t_input *input)
{
	char	**cmds;
	int		pipefd[2];
	int		in_fd;
	int		i;
	pid_t	pid;
	int		status;
	t_input	sub_input;

	i = 0;
	in_fd = 0;
	if (!ft_strchr(input->input, '|')) //cuidado lo pueden pasar en un echo "|"
	{
		ft_manage_input(input, STDIN_FILENO, STDOUT_FILENO);
		return ;
	}
	cmds = ft_split(input->input, '|');
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
			sub_input.input = ft_strtrim(cmds[i], " ");
			sub_input.envp = input->envp;
			ft_manage_input(&sub_input, STDIN_FILENO, STDOUT_FILENO);
			free(sub_input.input);
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
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
	ft_matrix_free(cmds);
}
