/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:49:18 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/01 23:22:35 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	nearest_to_exit(t_stack *stack, t_stack *b, size_t nodes)
{
	size_t	i;
	size_t	top_distance;
	size_t	tail_distance;
	size_t	nearest_exit;
	size_t	total_nodes;

	total_nodes = nodes + stacksize(b);
	i = total_nodes - 1 - 3;
	top_distance = 0;
	nearest_exit = nodes;
	while (stack)
	{
		while (stack && stack->index > i)
		{
			stack = stack->next;
			top_distance++;
		}
		tail_distance = nodes - top_distance - 1;
		if ((top_distance < nearest_exit) || (tail_distance < nearest_exit))
			nearest_exit = top_distance;
		top_distance++;
		if (stack)
			stack = stack->next;
	}
	return (nearest_exit);
}

void	order_b_to_a(t_stack **a, t_stack **b, size_t order)
{
	if (order == 12)
	{
		move_rotate(b, 'b');
		move_swap(b, 'b');
	}
	else if (order == 201)
	{
		move_swap(b, 'b');
		move_rotate(b, 'b');
	}
	else if (order == 120)
		move_swap(b, 'b');
	else if (order == 210)
		return ;
	else if (order == 21)
		move_rotate(b, 'b');
	else if (order == 102)
		move_inv_rotate(b, 'b');
	while (*b)
		move_push(b, a, 'a');
}

void	order_three(t_stack **stack, size_t order)
{
	if (order == 12)
		return ;
	else if (order == 201)
		move_rotate(stack, 'a');
	else if (order == 120)
		move_inv_rotate(stack, 'a');
	else if (order == 210)
	{
		move_swap(stack, 'a');
		move_inv_rotate(stack, 'a');
	}
	else if (order == 21)
	{
		move_inv_rotate(stack, 'a');
		move_swap(stack, 'a');
	}
	else if (order == 102)
		move_swap(stack, 'a');
}

void	make_three(t_stack **stack, t_stack **b, char c, size_t nodes)
{
	size_t	i;
	size_t	order;
	size_t	multiplier;
	t_stack	*aux;

	i = 0;
	order = 0;
	multiplier = 100;
	aux = *stack;
	nodes = nodes + stacksize(*b);
	while (i < 3)
	{
		order = order + multiplier * (aux->index - (nodes - 3));
		multiplier /= 10;
		aux = aux->next;
		i++;
	}
	if (c == 'a')
		order_three(stack, order);
	else
		order_b_to_a(stack, b, order);
}

/*we search for the n (1 to 3) minimums near to exit to B */
void	order_to_three(t_stack **a, t_stack **b, size_t nodes)
{
	size_t	top_distance;
	size_t	tail_distance;
	size_t	i;

	while (nodes > 3)
	{
		i = 0;
		top_distance = nearest_to_exit(*a, *b, nodes);
		tail_distance = nodes - top_distance - 1;
		if (top_distance < tail_distance)
		{
			while (i++ < top_distance)
				move_rotate(a, 'a');
		}
		else
		{
			while (i++ <= tail_distance)
				move_inv_rotate(a, 'a');
		}
		move_push(a, b, 'b');
		nodes = nodes - 1;
	}
	make_three(a, b, 'a', nodes);
	if (stacksize(*b) == 3)
		make_three(a, b, 'b', nodes);
	else if (stacksize(*b) == 2)
	{
		if ((*b)->value < (*b)->next->value)
			move_rotate(b, 'b');
		move_push(b, a, 'a');
		move_push(b, a, 'a');
	}
	else if (stacksize(*b) == 1)
		move_push(b, a, 'a');
}
