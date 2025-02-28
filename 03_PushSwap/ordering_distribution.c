/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ordering_distribution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:07:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/28 22:03:10 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_already_ordered(t_stack *a, size_t nodes)
{
	size_t	i;
	
	i = 0;
	while (i < nodes)
	{
		if (a->index != i)
			return (0);
		a = a->next;
		i++;
	}
	return (1);
}

void	ordering(t_stack **a, t_stack **b)
{
	size_t	chunck;
	size_t	nodes;

	nodes = stacksize(*a);
	if(check_already_ordered(*a, nodes))
		return ;
	
	chunck = brute_force(*a, b, nodes);
	if (chunck == 0)
		return ;
	if (nodes < 4)
		normal_sort(a, b, nodes);
	/* if (nodes < 20)
		return ; /// */
	else
		ksort(a, b, chunck);
}
