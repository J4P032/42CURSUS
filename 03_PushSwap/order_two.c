/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 11:03:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/02 18:31:22 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*depending on we are A or B will only rotate or also push to A from B*/
void	order_two(t_stack **a, t_stack **b, char c)
{
	if (c == 'a')
	{
		if ((*a)->value > (*a)->next->value)
			move_rotate(a, 'a');
	}
	else
	{
		if ((*b)->value < (*b)->next->value)
			move_rotate(b, 'b');
		move_push(b, a, 'a');
		move_push(b, a, 'a');
	}
}

/*moving up and down are comming from order_to_three*/
void	moving_up(t_stack **a, size_t top_distance, char c)
{
	size_t	i;

	i = 0;
	while (i < top_distance)
	{
		move_rotate(a, c);
		i++;
	}
}

void	moving_down(t_stack **a, size_t tail_distance, char c)
{
	size_t	i;

	i = 0;
	while (i <= tail_distance)
	{
		move_inv_rotate(a, c);
		i++;
	}
}
