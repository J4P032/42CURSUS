/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:56:18 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/22 13:30:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*runs the list from 'lst' node and applies the 'f' function into the content*/
/*NOTE!!! NOT possible to use in circular lists. Infinite*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*aux;

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
