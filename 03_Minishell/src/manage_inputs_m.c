/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_inputs_m.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:28:00 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/09 01:27:03 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"


void	ft_manage_input(t_input *input, int in_fd, int out_fd)
{
	input->inputfd = in_fd;
	input->outputfd = out_fd;

	// 🔥 Mover esta línea arriba
	handle_redirection(input);

	input->input_split = ft_split_quotes(input->input, ' ', input);
	if (!input->input_split || !input->input_split[0])
		return ; //CHEQUEAR NO LEAKS

	compose_command_args(input);

	//printf("command :%s\n", input->command);//
	//printf("arg :%s\n-------------\n", input->args);//

	if (ft_strcmp(input->command, "pwd") == 0)
		ft_pwd(input->args);
	else if (ft_strcmp(input->command, "cd") == 0)
		ft_cd(input->input_split, input->envp);
	else if (ft_strcmp(input->command, "echo") == 0)
		ft_echo(input);
	else if (ft_strcmp(input->command, "export") == 0 && input->input_split[1])
		ft_export(input->args, &input->envp);
	else if (ft_strcmp(input->command, "env") == 0)
		ft_env(input, input->envp);
	else if (ft_strcmp(input->command, "unset") == 0 && input->input_split[1])
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
