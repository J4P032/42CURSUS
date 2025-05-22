/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_m.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:07:20 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/22 17:05:56 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	ft_cd(t_input *input)
{
	char		*path;
	static char	oldpwd[4096] = "";
	char		prev[4096];

	if (input->split_exp[1] && input->split_exp[2])
	{
		printf("cd: too many arguments\n");
		input->last_exit_code = 1;
		return ;
	}
	if (!input->parsed[0])
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("cd: HOME not set\n");
			input->last_exit_code = 1;
			return ;
		}
	}
	else if (ft_strcmp(input->parsed, "-") == 0)
	{
		if (ft_strlen(oldpwd) == 0)
		{
			printf("cd: OLDPWD not set\n");
			input->last_exit_code = 1;
			return ;
		}
		printf("%s\n", oldpwd);
		path = oldpwd;
	}
	else
		path = input->parsed;

	if (getcwd(prev, sizeof(prev)) == NULL)
		{
			printf("getcwd");
			input->last_exit_code = 1;
			return ;
		}
	if (chdir(path) != 0)
		{
			perror("cd");
			input->last_exit_code = 1;
			return ;
		}
	ft_strlcpy(oldpwd, prev, sizeof(oldpwd));
	input->last_exit_code = 0;
}

