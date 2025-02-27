/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ksort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:28:15 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/27 16:53:11 by jrollon-         ###   ########.fr       */
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

void	move_up(t_stack **a, t_stack **b, t_stack *aux)
{
	while (aux->prev)
		move_rotate(b, 'b');
	move_push(b, a, 'a');		
}

void	move_down(t_stack **a, t_stack **b, t_stack *aux)
{
	while (aux->prev)
		move_inv_rotate(b, 'b');
	move_push(b, a, 'a');		
}

void	final_order(t_stack **a, t_stack **b, size_t s_index)
{
	t_stack	*aux;
	size_t	i;
	size_t	head_distance;
	size_t	tail_distance;
	
	i = 0;
	s_index = s_index - 1;
	while (*b)
	{
		head_distance = 0;
		aux = *b;
		while (aux->index != s_index - i)
		{
			head_distance++;
			aux = aux->next;
		}
		tail_distance = s_index - i - head_distance;
		if (tail_distance >= head_distance)
			move_up(a, b, aux);
		else
		 	move_down(a, b, aux);
		i++;
	}
	
}

/* void	ksort(t_stack **a, t_stack **b)
{
	double	range;
	size_t	nodes;

	nodes = stacksize(*a);
	range = (ft_sqrt(nodes) * 133) / 100;
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
} */

void	ksort(t_stack **a, t_stack **b)
{
	double	range;
	size_t	nodes;
	size_t	i;
	
	i = 0;
	nodes = stacksize(*a);
	range = ft_sqrt(nodes) * 133 / 100;
	while (*a)
	{
		if ((*a)->index <= i)
		{
			move_push(a, b, 'b');
			move_rotate(b, 'b');
		}
		else if (i < (*a)->index && (*a)->index <= i + range)
			move_push(a, b, 'b');
		else if ((*a)->index > i + range)
			move_rotate(a, 'a');
		i++;
	}
	final_order(a, b, nodes);
}

