/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env_m.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:24:39 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/28 11:55:40 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	ft_env(char **input)
{
	int	i;

	if (input[1] && input[1][0] == '-' && input[1][1])
		printf("env: invalid option -- %c\n", input[1][1]);
	else if (input[1] && input[1][0] != '-')
		printf("env:'%s': No such file or directory\n", input[1]);
	else
	{
		i = 0;
		while (environ[i])
		{
			printf("%s\n", environ[i]);
			i++;
		}
	}
}
