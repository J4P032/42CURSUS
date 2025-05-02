/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo_m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:50:16 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/02 19:36:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	ft_echo(char **input, t_input *in)
{
	int		i;

	i = 1;
	if (ft_strcmp(input[1], "-n") == 0)
		i = 2;
	while (input[i])
	{
		if (in->spaced[i])
			printf(" %s", input[i]);
		else
			printf("%s", input[i]);
		i++;
	}
	if (ft_strcmp(input[1], "-n") != 0)
		printf("\n");
}
