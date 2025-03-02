/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:49:18 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/02 18:29:49 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*This calculates the 3 lowest numbers in the stack and returns which one...*/
/*it is the shortest distance to raise to top of the stack*/
/*total_nodes is needed for B stack in i = total_nodes - 1 - 3;... */
/*...imagine 6 nodes and we want to process 3 in B. nodes pased is 3, but...*/
/*...total_nodes=6 so i=6-1-3=3. We search for indexes lower than 3 (0 1 2) */
/*...but if we search in A we search for same indexes that way*/
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

/*Order must be lower botton upper higher, then once done push all to B*/
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
	else if (order == 21)
		move_rotate(b, 'b');
	else if (order == 102)
		move_inv_rotate(b, 'b');
	while (*b)
		move_push(b, a, 'a');
}

/*With the sorted final indexes composed we make the right moves*/
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

/*we produce in number the conjuntion of all index to compare later and...*/
/*...produce the right movements to be ordered those 3 nodes of A or B*/
/*IMPORTANT! order has to be updated to index as if only where 3 nodes*/
/*that is the reason of aux->index - (nodes - 3) because imagine 4 nodes*/
/*...order would be 312 or 231 when we search for 201 or 120 */
/*IMPORTANT! if we want to order B with 3 nodes in arguments must be 0...*/
/*...as it will update nodes = nodes + stacksize(*b); with 3 or B so...*/
/*...aux->index - (3 - 3) = the real 0, 1 or 2 index */
void	make_three(t_stack **stack, t_stack **b, char c, size_t nodes)
{
	size_t	i;
	size_t	order;
	size_t	multiplier;
	t_stack	*aux;

	i = 0;
	order = 0;
	multiplier = 100;
	if (c == 'a')
		aux = *stack;
	else
		aux = *b;
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
/*Depending of number of nodes it will process different in B*/
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
			moving_up(a, top_distance, 'a');
		else
			moving_down(a, tail_distance, 'a');
		move_push(a, b, 'b');
		nodes = nodes - 1;
	}
	make_three(a, b, 'a', nodes);
	if (stacksize(*b) == 3)
		make_three(a, b, 'b', 0);
	else if (stacksize(*b) == 2)
		order_two(a, b, 'b');
	else if (stacksize(*b) == 1)
		move_push(b, a, 'a');
}
