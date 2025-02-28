/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute_force.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:13:16 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/28 20:47:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	copy_node(t_stack *a, t_stack **a_copy, t_stack *node)
{
	t_stack	*aux;

	aux = NULL;
	node->value = a->value;
	node->index = a->index;
	if ((!*a_copy))
	{
		node->next = NULL;
		node->prev = NULL;
		*a_copy = node;
		return ;
	}
	aux = *a_copy;
	while (aux->next)
		aux = aux->next;
	aux->next = node;
	node->next = NULL;
	node->prev = aux;
}

t_stack	*copy_stack(t_stack *a, size_t num_nodes)
{
	t_stack	*a_copy;
	t_stack *node;
	size_t	i;

	i = 0;
	a_copy = NULL;
	while (i < num_nodes)
	{
		node = ft_calloc(1, sizeof(t_stack));
		if (!node)
		{
			ft_free((void **)&a_copy, 1); //mirar si lo hace bien en caso de fallo de memoria
			return (NULL);
		}
		copy_node (a, &a_copy, node);
		i++;
		a = a->next;
	}
	return (a_copy);
}

#include <stdio.h> ////
size_t	brute_force(t_stack *a, t_stack **b, size_t nodes)
{
	t_stack	*a_copy;
	size_t	movements;
	size_t	min_moves;
	size_t	best_i;
	size_t	i;

	i = 1;
	best_i = i;
	min_moves = 2147483647;
	while (i <= 30)
	{
		movements = 0;
		a_copy = copy_stack(a, nodes);
		if (!a_copy)
			return (0);
		sim_ksort(&a_copy, b, i, &movements);
		if (movements < min_moves)
		{
			min_moves = movements;	
			best_i = i;
		}
		i++;
		ft_free((void **)&a_copy, 1);
	}
	return (best_i);
}
