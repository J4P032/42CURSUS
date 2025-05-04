/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env_m.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:24:39 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/03 11:23:25 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	ft_env(char **input, char **envp)
{
	int	i;

	if (input[1] && input[1][0] == '-' && input[1][1])
		printf("env: invalid option -- %c\n", input[1][1]);
	else if (input[1] && input[1][0] != '-')
		printf("env:'%s': No such file or directory\n", input[1]);
	else
	{
		i = 0;
		while (envp && envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
}
