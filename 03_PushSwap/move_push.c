/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:39:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/02 15:10:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	write_push(char c)
{
	write(1, "p", 1);
	write(1, &c, 1);
	write(1, "\n", 1);
}

/*pa or pb movements*/
void	move_push(t_stack **stack1, t_stack **stack2, char c)
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
	write_push(c);
}
