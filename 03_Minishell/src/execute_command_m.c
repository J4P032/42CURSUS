/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_m.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:49:50 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/05 20:12:54 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

// Devuelve el valor de la variable de entorno PATH.
char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

// Concatena un directorio y comando en una ruta completa.
char	*join_path(const char *dir, const char *command)
{
	char	*full_path;
	size_t	len;

	len = ft_strlen(dir) + ft_strlen(command) + 2;
	full_path = ft_calloc(1, len * sizeof(char));
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, command, len);
	return (full_path);
}

// Busca un ejecutable en los directorios de PATH.
char	*find_executable(char *command, char **envp)
{
	char	*path;
	char	**dirs;
	char	*full_path;
	int		i;

	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	path = get_path_env(envp);
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_path = join_path(dirs[i++], command);
		if (full_path && access(full_path, X_OK) == 0)
			return (ft_matrix_free(dirs), full_path);
		free(full_path);
	}
	ft_matrix_free(dirs);
	return (NULL);
}

bool	exec_child(t_input *input, pid_t pid, char *executable)
{
	char **command_union;
		
	if (input->args[0])
		command_union = (char **)ft_calloc(3, sizeof(char *));
	else
		command_union = (char **)ft_calloc(2, sizeof(char *));
	if (!command_union)
		return (false); ///chequear bien que libere bien memoria.
	command_union[0] = input->command;
	if (input->args[0])
		command_union[1] = input->args;
	
	if (pid == -1)
	{
		perror("fork");
		free(executable);
		if (command_union)
			free (command_union);
		command_union = NULL;
		return (false);
	}
	if (pid == 0)
	{
		if (input->inputfd != STDIN_FILENO)
			dup2(input->inputfd, STDIN_FILENO);
		if (input->outputfd != STDOUT_FILENO)
			dup2(input->outputfd, STDOUT_FILENO);
		execve(executable, command_union, input->envp);
		if (command_union)
			free (command_union);
		command_union = NULL;
		free(executable);
		exit(1);
	}
	
	return (free (command_union), true);
}

// Ejecuta un comando en un proceso hijo con redirección.
bool	execute_command(t_input *input)
{
	char	*executable;
	pid_t	pid;
	int		status;

	if (!input->input_split || !input->input_split[0])
		return (false);
	executable = find_executable(input->command, input->envp);
	if (!executable)
	{
		printf("%s: command not found\n", input->command);
		return (false);
	}
	pid = fork();
	if (exec_child(input, pid, executable) == 0)
		return (free(executable), false);///chequear
	waitpid(pid, &status, 0);
	free(executable);
	return (WIFEXITED(status) && WEXITSTATUS(status) == 0);
}
