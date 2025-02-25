/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:40:46 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/25 20:55:15 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*last_node(t_stack *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

void	move_inv_rotate(t_stack **stack, char c)
{
	t_stack	*aux;
	t_stack	*tail;

	if (!stack || !*stack)
		return ;
	aux = (*stack)->next;
	if (aux)
	{
		tail = last_node(*stack);
		tail->next = (*stack);
		(*stack)->prev = tail;
		tail->prev->next = NULL;
		(*stack) = tail;
		if (c == 'a' || c == 'b')
		{
			write(1, "rr", 2);
			write(1, &c, 1);
			write(1, "\n", 1);
		}
	}
}

void	move_rotate(t_stack **stack, char c)
{
	t_stack *aux;
	t_stack	*tail;

	if (!stack || !*stack)
		return ;
	aux = (*stack)->next;
	if (aux)
	{
		tail = last_node(*stack);
		tail->next = (*stack);
		(*stack)->next = NULL;
		(*stack)->prev = tail;
		(*stack) = aux;
		(*stack)->prev = NULL;
		if (c == 'a' || c == 'b')
		{
			write(1, "r", 1);
			write(1, &c, 1);
			write(1, "\n", 1);
		}
	}
}

void	double_rotate(t_stack **stack1, t_stack **stack2)
{
	if ((*stack1)->next && (*stack2)->next)
	{
		move_rotate(stack1, '0');
		move_rotate(stack2, '0');
		write(1, "rr", 2);
	}
	else if ((*stack1)->next)
		move_rotate(stack1, 'a');
	else if ((*stack2)->next)
		move_rotate(stack2, 'b');
}

void	double_inv_rotate(t_stack **stack1, t_stack **stack2)
{
	if ((*stack1)->next && (*stack2)->next)
	{
		move_inv_rotate(stack1, '0');
		move_inv_rotate(stack2, '0');
		write(1, "rrr", 3);
	}
	else if ((*stack1)->next)
		move_inv_rotate(stack1, 'a');
	else if ((*stack2)->next)
		move_inv_rotate(stack2, 'b');
}


