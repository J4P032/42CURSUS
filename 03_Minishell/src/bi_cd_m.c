/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_m.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:07:20 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/20 00:16:28 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

bool	ft_cd(t_input *input)
{
	char		*path;
	static char	oldpwd[4096] = "";
	char		prev[4096];

	if (!input->parsed[0])
	{
		path = getenv("HOME");
		if (!path)
			return (printf("cd: HOME not set\n"), 1);
	}
	else if (ft_strcmp(input->parsed, "-") == 0)
	{
		if (ft_strlen(oldpwd) == 0)
			return (printf("cd: OLDPWD not set\n"), 1);
		printf("%s\n", oldpwd);
		path = oldpwd;
	}
	else
		path = input->parsed;
	if (getcwd(prev, sizeof(prev)) == NULL)
		return (perror("getcwd"), 1);
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	ft_strlcpy(oldpwd, prev, sizeof(oldpwd));
	return (0);
}

