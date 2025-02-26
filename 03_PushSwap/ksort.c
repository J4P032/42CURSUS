/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ksort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:28:15 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/26 22:00:03 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	stacksize(t_stack *stack)
{
	size_t	i;

	i = 0;
	while (stack)
	{
		i++;
		stack = stack->next;
	}
	return (i);
}

void	ksort(t_stack **a, t_stack **b)
{
	double	range;
	size_t	nodes;

	nodes = stacksize(*a);
	range = (nodes * 133) / 100;
	while (*a)
	{
		if ((*a)->index <= nodes)
		{
			move_push(a, b, 'b');
			move_rotate(b, 'b');
		}
		else if (nodes < (*a)->index && (*a)->index <= nodes + range)
			move_push(a, b, 'b');
		else if ((*a)->index > nodes + range)
			move_rotate(a, 'a');
		nodes = nodes - 1;
	}
}

/* void	ksort(t_stack **a, t_stack **b)
{
	double	range;
	size_t	nodes;
	size_t	i;

	i = 0;
	nodes = stacksize(*a);
	range = (nodes * 133) / 100;
	while (*a)
	{
		if (nodes <= i)
		{
			move_push(a, b, 'b');
			move_rotate(b, 'b');
		}
		else if (nodes < i && i <= nodes + range)
			move_push(a, b, 'b');
		else if (i > nodes + range)
			move_rotate(a, 'a');
		nodes = nodes - 1;
		i++;
	}
} */


