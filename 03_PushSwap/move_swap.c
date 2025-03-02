/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:39:08 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/02 15:14:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*sa or sb movements*/
void	move_swap(t_stack **stack, char c)
{
	t_stack	*aux;

	if (!stack || !*stack)
		return ;
	if ((*stack)->next)
	{
		aux = (*stack)->next;
		if (aux->next)
		{
			(*stack)->next = aux->next;
			aux->next->prev = *stack;
		}
		else
			(*stack)->next = NULL;
		aux->next = (*stack);
		(*stack)->prev = aux;
		(*stack) = aux;
		if ('a' == c || 'b' == c)
		{
			write(1, "s", 1);
			write(1, &c, 1);
			write(1, "\n", 1);
		}
	}
}

/*ss double swap movement*/
void	double_swap(t_stack **stack1, t_stack **stack2)
{
	if ((*stack1)->next && (*stack2)->next)
	{
		move_swap(stack1, '0');
		move_swap(stack2, '0');
		write(1, "ss\n", 3);
	}
	else if ((*stack1)->next)
		move_swap(stack1, 'a');
	else if ((*stack2)->next)
		move_swap(stack2, 'b');
}
