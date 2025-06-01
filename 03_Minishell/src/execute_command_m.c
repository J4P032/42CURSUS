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

static char	*join_path_cmd(char *dir, char *cmd)
{
	size_t	len;
	char	*full;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full = malloc(len);
	if (!full)
		return (NULL);
	ft_strlcpy(full, dir, ft_strlen(dir) + 1);
	ft_strcat(full, "/");
	ft_strcat(full, cmd);
	return (full);
}

static char	*search_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = NULL;
	full_path = NULL;
	i = 0;
	while (*envp && strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (*envp)
		paths = ft_split(*envp + 5, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_path = join_path_cmd(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			ft_matrix_free(&paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_matrix_free(&paths);
	return (NULL);
}

char	*get_cmd_path_from_env(t_input *input, char **envp, char *cmd)
{
	struct stat	st;
	char		*path;

	if (!cmd || *cmd == '\0')
	{
		ft_putstr_fd("minishell: Permission denied\n", 2);
		exit(1);
	}
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
		{
			perror(cmd);
			exit(127);
		}
		if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("minishell: Is a directory\n", 2);
			exit(126);
		}
		if (access(cmd, X_OK) != 0)
		{
			input->last_exit_code = 0;
			exit(126);
		}
		return (ft_strdup(cmd));
	}
	path = search_path(cmd, envp);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		exit(127);
	}
	return (path);
}



static void	child_process(t_input *input)
{
	char	*cmd_path;

	//printf("Command: %s\n", input->command);
	cmd_path = get_cmd_path_from_env(input, input->envp, input->command);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(input->command, 2);
		ft_putchar_fd('\n', 2);
		exit(127);
	}
	if (input->inputfd != STDIN_FILENO && dup2(input->inputfd, STDIN_FILENO) == -1)
	{
		perror("dup2 inputfd");
		exit(1);
	}
	if (input->outputfd != STDOUT_FILENO && dup2(input->outputfd, STDOUT_FILENO) == -1)
	{
		perror("dup2 outputfd");
		exit(1);
	}
	if (input->parsed)
		free(input->parsed);
	
	//SEÑALES DE JAVI NO BORRAR!!!!
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	
	execve(cmd_path, input->split_exp, input->envp);
	if (errno == ENOEXEC)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->command, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(cmd_path);
		exit(2);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->command, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free(cmd_path);
		exit(126);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->command, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(cmd_path);
		exit(127);
	}
	perror("execve");
	free(cmd_path);
	exit(1);
}

bool	execute_command(t_input *input)
{
	pid_t				pid;
	int					status;
	struct sigaction	sa; ///NO BORRAR!!! SEÑALES

	// Ignorar señales en padre mientras hijo corre no preocuparse por rayas rojas..
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

	pid = fork();
	if (pid < 0)
		return (perror("fork"), false);
	if (pid == 0)
		child_process(input);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			return (perror("waitpid"), false);
		
		
		init_sigaction(&sa); ///NO BORRAR!!! SEÑALES
		if (WIFEXITED(status))
			input->last_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			int sig;

			sig = WTERMSIG(status);
			if (sig == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
			input->last_exit_code = 128 + sig;
		}
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
