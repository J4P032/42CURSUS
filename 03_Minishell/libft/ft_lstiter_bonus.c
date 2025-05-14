/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:56:18 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/14 15:15:20 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_lists *lst, void (*f)(void *))
{
	t_lists	*aux;

	if (!lst)
		return ;
	aux = lst;
	while (aux)
	{
		if (f)
			f(aux->content);
		aux = aux->next;
	}
}
