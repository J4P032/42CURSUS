/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:01:44 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/26 18:19:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	counting_sort(t_stack *stack)
{
	t_stack	*aux;
	t_stack	*running;
	size_t	i;

	aux = stack;
	while (aux)
	{
		running = stack;
		i = 0;
		while (running)
		{
			if (running->value < aux->value)
				i++;
			running = running->next;
		}
		aux->index = i;
		aux = aux->next;
	}
}
