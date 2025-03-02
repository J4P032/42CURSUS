/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ordering_distribution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:07:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/02 18:38:47 by jrollon-         ###   ########.fr       */
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

/*check_already_ordered is to not make any movement if already order*/
/*from 7 numbers we start to make ksort as it is great aproximation*/
void	ordering(t_stack **a, t_stack **b)
{
	size_t	chunck;
	size_t	nodes;

	chunck = 0;
	nodes = stacksize(*a);
	if (check_already_ordered(*a, nodes))
		return ;
	if (nodes < 8)
		normal_sort(a, b, nodes);
	if (nodes > 7)
	{
		chunck = brute_force(*a, b, nodes);
		if (chunck == 0)
			return ;
		ksort(a, b, chunck);
	}
}
