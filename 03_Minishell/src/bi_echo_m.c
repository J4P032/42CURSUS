/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo_m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:50:16 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/28 12:00:56 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	ft_echo(char **input)
{
	int		i;
	bool	space;

	space = 0;
	i = 1;
	if (ft_strcmp(input[1], "-n") == 0)
		i = 2;
	while (input[i])
	{
		if (space)
			printf(" %s", input[i]);
		else
			printf("%s", input[i]);
		space = 1;
		i++;
	}
	if (ft_strcmp(input[1], "-n") != 0)
		printf("\n");
}
