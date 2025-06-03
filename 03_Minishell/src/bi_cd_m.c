/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_m.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:07:20 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/30 14:49:14 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

char	*get_env_value(char **envp, const char *name)
{
	int		i;
	size_t	len;

	if (!envp || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (&envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

static char	*get_cd_path(t_input *input, char *oldpwd)
{
	char	*home;

	if (!input->parsed[0])
	{
		home = get_env_value(input->envp, "HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			input->last_exit_code = 1;
			return (NULL);
		}
		return (home);
	}
	if (ft_strcmp(input->parsed, "-") == 0)
	{
		if (ft_strlen(oldpwd) == 0)
		{
			printf("cd: OLDPWD not set\n");
			input->last_exit_code = 1;
			return (NULL);
		}
		printf("%s\n", oldpwd);
		return (oldpwd);
	}
	return (input->parsed);
}

static void	ft_update_pwd_env(t_input *input, char *prev, char *oldpwd)
{
	char	newpwd[4096];

	if (!getcwd(newpwd, sizeof(newpwd)))
	{
		perror("getcwd");
		input->last_exit_code = 1;
		return ;
	}
	update_env(input, "PWD", newpwd);
	update_env(input, "OLDPWD", prev);
	ft_strlcpy(oldpwd, prev, sizeof(oldpwd));
	input->last_exit_code = 0;
}

void	ft_cd(t_input *input)
{
	char		*path;
	static char	oldpwd[4096];
	char		prev[4096];

	if (input->split_exp[1] && input->split_exp[2])
	{
		write(2, "miniyo: cd: too many arguments\n", 32);
		input->last_exit_code = 1;
		return ;
	}
	if (!getcwd(prev, sizeof(prev)))
	{
		perror("getcwd");
		input->last_exit_code = 1;
		return ;
	}
	path = get_cd_path(input, oldpwd);
	if (!path || chdir(path) != 0)
	{
		if (path)
			ft_printf("%s: No such file or directory\n", path);
		input->last_exit_code = 1;
		return ;
	}
	ft_update_pwd_env(input, prev, oldpwd);
}
