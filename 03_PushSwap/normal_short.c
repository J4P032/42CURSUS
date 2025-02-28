/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_short.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 21:02:43 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/28 22:10:48 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	normal_sort(t_stack **a, t_stack **b, size_t nodes)
{
	t_stack	*aux;
	size_t	i;
	size_t	sorted_distance;
	size_t	sorted_position;
	size_t	tail_distance;
	
	(void)tail_distance;
	(void)sorted_position;
	(void)*b;

	
	i = 0;
	while (*a)
	{
		sorted_position = i;
		sorted_distance = 0;
		aux = *a;
		while (aux->index != i)
		{
			sorted_distance = sorted_distance - i;
			aux = aux->next;
		}
		tail_distance = (nodes - 1) - sorted_distance;
		/* if (tail_distance >= sorted_distance)
			move_up(a, b, aux);
		else
		 	move_down(a, b, aux); */
		i++;
	}
}



