/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ksort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:28:15 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/02 15:09:01 by jrollon-         ###   ########.fr       */
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
	while (*b != aux)
		move_rotate(b, 'b');
	move_push(b, a, 'a');
}

void	move_down(t_stack **a, t_stack **b, t_stack *aux)
{
	while (*b != aux)
		move_inv_rotate(b, 'b');
	move_push(b, a, 'a');
}

/*s_index is starting with number of nodes in B that way we...*/
/*...search for the biggest number of all of them that was in A...*/
/*...and make exit to A again through the mininum distance to...*/
/*...top of B to be transfer to A. This process is repeated until !B*/
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

/*it creates 3 ranges of numbers depending on final sort index*/
/*first if are very low numbers that are sent to B and to botton of it*/
/*2nd if are numbers bigger but small enough to just push to B*/
/*3rd if are out of range big ones that are jumped in A to next ones*/
/*with that behaviour we achieve '<' form bigger numers in borders...*/
/*...smaller in center so less movements to turn bigger into B once...*/
/*...finished process all numbers in A. Chunck comes from brute force*/
void	ksort(t_stack **a, t_stack **b, size_t chunck)
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
			move_push(a, b, 'b');
			move_rotate(b, 'b');
			i++;
		}
		else if (i < (*a)->index && (*a)->index <= i + range)
		{
			move_push(a, b, 'b');
			i++;
		}
		else if ((*a)->index > i + range)
			move_rotate(a, 'a');
	}
	final_order(a, b, nodes);
}
