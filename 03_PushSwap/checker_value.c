/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:23:50 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/26 21:33:56 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	checker_value(t_stack **aux, t_stack *node, int value, int *error)
{
	while ((*aux)->next)
	{
		if ((*aux)->value == value)
		{
			*error = 1;
			free(node);
			return ;
		}
		(*aux) = (*aux)->next;
	}
	if ((*aux)->value == value)
	{
		*error = 1;
		free(node);
	}
}
