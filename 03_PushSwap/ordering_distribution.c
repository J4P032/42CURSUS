/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ordering_distribution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:07:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/28 14:07:28 by jrollon-         ###   ########.fr       */
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

int	check_already_ordered(t_stack *a, size_t nodes)
{
	size_t	i;
	
	i = 0;
	while (i < nodes)
	{
		if (a->index != i)
			return (0);
		a = a->next;
		i++;
	}
	return (1);
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


#include <stdio.h> ///
void	ordering(t_stack **a, t_stack **b)
{
	t_stack	*a_copy;
	size_t	chunck;
	size_t	nodes;

	(void)chunck;
	(void)*b;
	nodes = stacksize(*a);
	if(check_already_ordered(*a, nodes))
		return ;
	a_copy = copy_stack(*a, nodes);
	if (!a_copy)
		return ;
	if (nodes < 20)
		return ; ///
	
	ft_free((void **)&a_copy, 1);
	
	ksort(a, b);
}
