/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_short.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 21:02:43 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/03 09:04:18 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	remove_from_b(t_stack **a, t_stack **b, size_t nodes)
{
	size_t	top_distance;
	size_t	tail_distance;
	t_stack	*aux;

	top_distance = 0;
	aux = *b;
	while (aux && aux->index < (nodes - 1))
	{
		aux = aux->next;
		top_distance++;
	}
	tail_distance = nodes - top_distance - 1;
	if (top_distance < tail_distance)
		moving_up(b, top_distance, 'b');
	else
		moving_down(b, tail_distance, 'b');
	move_push(b, a, 'a');
}

void	normal_sort(t_stack **a, t_stack **b, size_t nodes)
{
	if (nodes == 2)
		order_two(a, b, 'a');
	if (nodes == 3)
		make_three(a, b, 'a', nodes);
	if (nodes > 3 && nodes < 7)
		order_to_three(a, b, nodes);
	if (nodes == 7)
	{
		order_to_three(a, b, nodes);
		remove_from_b(a, b, 4);
		make_three(a, b, 'b', 0);
	}
}
