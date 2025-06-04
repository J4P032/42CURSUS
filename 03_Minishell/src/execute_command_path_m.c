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
			return (ft_matrix_free(&paths), full_path);
		free(full_path);
		i++;
	}
	ft_matrix_free(&paths);
	return (NULL);
}

static void	exit_if_invalid_cmd(char *cmd)
{
	if (!cmd || *cmd == '\0')
	{
		ft_putstr_fd("miniyo: Permission denied\n", 2);
		exit(1);
	}
}

static void	handle_slash_path(t_input *input, char *cmd)
{
	struct stat	st;

	if (access(cmd, F_OK) != 0)
	{
		perror(cmd);
		exit(127);
	}
	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("miniyo: Is a directory\n", 2);
		exit(126);
	}
	if (access(cmd, X_OK) != 0)
	{
		input->last_exit_code = 0;
		exit(126);
	}
}

char	*get_cmd_path_from_env(t_input *input, char **envp, char *cmd)
{
	char	*path;

	exit_if_invalid_cmd(cmd);
	if (ft_strchr(cmd, '/'))
	{
		handle_slash_path(input, cmd);
		return (ft_strdup(cmd));
	}
	path = search_path(cmd, envp);
	if (!path)
	{
		ft_putstr_fd("miniyo: command not found\n", 2);
		exit(127);
	}
	return (path);
}
