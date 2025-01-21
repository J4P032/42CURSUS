/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:44:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/21 21:17:50 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*aux;

	if (!*lst || !lst)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		if (del)
			del((*lst)->content);
		free(*lst);
		*lst = aux;
	}
	*lst = NULL;
}
