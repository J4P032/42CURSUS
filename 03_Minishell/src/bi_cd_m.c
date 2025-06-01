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

static char	*get_cd_path(t_input *input, char *oldpwd)
{
	if (!input->parsed[0])
	{
		if (!getenv("HOME"))
		{
			printf("cd: HOME not set\n");
			input->last_exit_code = 1;
			return (NULL);
		}
		return (getenv("HOME"));
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

char	*make_env_var(const char *name, const char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

void	ft_cd(t_input *input)
{
	char			*path;
	static char		oldpwd[4096] = "";
	char			prev[4096];
	//char			newpwd[4096];

	if (input->split_exp[1] && input->split_exp[2])
	{
		ft_putstr_fd("miniyo: cd: too many arguments\n", 2);
		input->last_exit_code = 1;
		return ;
	}
	if (getcwd(prev, sizeof(prev)) == NULL)
	{
		perror("getcwd");
		input->last_exit_code = 1;
		return ;
	}
	path = get_cd_path(input, oldpwd);
	if (!path)
		return ;
	if (chdir(path) != 0)
	{
		perror("cd");
		input->last_exit_code = 1;
		return ;
	}
	ft_strlcpy(oldpwd, prev, sizeof(oldpwd));
	//if (getcwd(newpwd, sizeof(newpwd)) != NULL)
	//	update_env_pwd(input, oldpwd, newpwd);
	input->last_exit_code = 0;
}
