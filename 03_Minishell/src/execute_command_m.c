/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_m.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:49:50 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/29 22:55:37 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

static void	setup_redirects(t_input *input)
{
	if (input->inputfd != STDIN_FILENO)
	{
		if (dup2(input->inputfd, STDIN_FILENO) == -1)
		{
			perror("dup2 inputfd");
			exit(1);
		}
	}
	if (input->outputfd != STDOUT_FILENO)
	{
		if (dup2(input->outputfd, STDOUT_FILENO) == -1)
		{
			perror("dup2 outputfd");
			exit(1);
		}
	}
}

static void	handle_exec_error(t_input *input, char *cmd_path)
{
	if (errno == ENOEXEC || errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->command, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(cmd_path);
		if (errno == ENOEXEC)
			exit(2);
		exit(127);
	}
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->command, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free(cmd_path);
		exit(126);
	}
	perror("execve");
	free(cmd_path);
	exit(1);
}

void	child_process(t_input *input)
{
	char	*cmd_path;

	cmd_path = get_cmd_path_from_env(input, input->envp, input->command);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(input->command, 2);
		ft_putchar_fd('\n', 2);
		exit(127);
	}
	setup_redirects(input);
	if (input->parsed)
		free(input->parsed);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd_path, input->split_exp, input->envp);
	handle_exec_error(input, cmd_path);
}

bool	execute_command(t_input *input)
{
	pid_t				pid;
	int					status;
	struct sigaction	sa;
	int					sig;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), false);
	if (pid == 0)
		child_process(input);
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), false);
	init_sigaction(&sa);
	if (WIFEXITED(status))
		input->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		input->last_exit_code = 128 + sig;
	}
	return (true);
}

/*
ft_printf("-----START-----\n"); 
ft_printf("command:%s\n", input->command);
ft_printf("arg:%s\n", input->args);
ft_printf("parsed:%s\n", input->parsed);
for (size_t i = 0; input->input_split[i]; i++)
	ft_printf("Input_split%d:%s %d\n", i, input->input_split[i],
		 input->status_exp[i]);
for (size_t i = 0; input->split_exp[i]; i++)
	ft_printf("Split_exp%d:%s %d\n", i, input->split_exp[i],
		 input->status_exp[i]);
ft_printf("inputfd:%d\n", input->inputfd);
ft_printf("outputfd:%d\n", input->outputfd);
ft_printf("-----END-----\n"); 
*/
