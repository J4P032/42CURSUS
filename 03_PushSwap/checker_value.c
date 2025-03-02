/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:23:50 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/02 14:55:15 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*Checks if the value readed from argv is already in the stack if so error=1*/
/*final check again because if not last node wouldnt be checked*/
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
