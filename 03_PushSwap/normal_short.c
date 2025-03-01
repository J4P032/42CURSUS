/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_short.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 21:02:43 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/01 21:57:00 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	normal_sort(t_stack **a, t_stack **b, size_t nodes)
{
	if (nodes == 3)
		make_three(a, b, 'a', nodes);
	if (nodes > 3 && nodes < 7)
		order_to_three(a, b, nodes);


}



