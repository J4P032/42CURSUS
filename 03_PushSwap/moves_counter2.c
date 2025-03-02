/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_counter2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:41:33 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/02 15:18:52 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sim_move_up(t_stack **a, t_stack **b, t_stack *aux, size_t *moves)
{
	while (*b != aux)
		simulate_rotate(b, moves);
	simulate_push(b, a, moves);
}

void	sim_move_down(t_stack **a, t_stack **b, t_stack *aux, size_t *moves)
{
	while (*b != aux)
		simulate_inv_rotate(b, moves);
	simulate_push(b, a, moves);
}

void	sim_order(t_stack **a, t_stack **b, size_t s_index, size_t *moves)
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
			sim_move_up(a, b, aux, moves);
		else
			sim_move_down(a, b, aux, moves);
		i++;
	}
}
