/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_m.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:07:20 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/28 17:15:57 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

//char		cwd[4096];
bool	ft_cd(char **args, char **envp)
{
	char		*path;
	static char	oldpwd[4096] = "";

	(void)envp;
	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
			return (printf("cd: HOME not set\n"), 1);
	}
	else if (ft_strcmp(args[1], "-") == 0 || ft_strcmp(args[1], "..") == 0)
	{
		if (ft_strlen(oldpwd) == 0)
			return (printf("cd: OLDPWD not set\n"), 1);
		path = oldpwd;
		printf("%s\n", path);
	}
	else
		path = args[1];
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		return (perror("getcwd"), 1);
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	return (0);
}
