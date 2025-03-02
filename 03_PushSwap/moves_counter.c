/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:14:07 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/02 15:16:48 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*these functions do the same as the real ones but do not write anything...*/
/*only count movements to record how many it does and then choose the minor*/
void	simulate_push(t_stack **stack1, t_stack **stack2, size_t *moves)
{
	t_stack	*aux;

	if (!stack1 || !*stack1)
		return ;
	aux = (*stack1)->next;
	if (*stack2)
	{
		(*stack2)->prev = (*stack1);
		(*stack1)->next = (*stack2);
		(*stack2) = (*stack1);
		(*stack1) = aux;
		if (aux)
			aux->prev = NULL;
	}
	else
	{
		(*stack2) = (*stack1);
		(*stack2)->next = NULL;
		(*stack2)->prev = NULL;
		(*stack1) = aux;
		if (aux)
			aux->prev = NULL;
	}
	*moves = *moves + 1;
}

void	simulate_inv_rotate(t_stack **stack, size_t *moves)
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
		*moves = *moves + 1;
	}
}

void	simulate_rotate(t_stack **stack, size_t *moves)
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
		(*stack)->next = NULL;
		(*stack)->prev = tail;
		(*stack) = aux;
		(*stack)->prev = NULL;
		*moves = *moves + 1;
	}
}

void	sim_ksort(t_stack **a, t_stack **b, size_t chunck, size_t *moves)
{
	int		range;
	size_t	nodes;
	size_t	i;

	i = 0;
	nodes = stacksize(*a);
	range = nodes / chunck;
	while (*a)
	{
		if ((*a)->index <= i)
		{
			simulate_push(a, b, moves);
			simulate_rotate(b, moves);
			i++;
		}
		else if (i < (*a)->index && (*a)->index <= i + range)
		{
			simulate_push(a, b, moves);
			i++;
		}
		else if ((*a)->index > i + range)
			simulate_rotate(a, moves);
	}
	sim_order(a, b, nodes, moves);
}
