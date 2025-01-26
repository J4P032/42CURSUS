/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:26:28 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/22 12:17:07 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*runs the list and apply f to content each node*/
/*create a new list and fills it with f(lst->content) of each node*/
/*problems then use del(lst->content)*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst2;
	t_list	*new_node;
	void	*filled;

	if (!lst || !f || !del)
		return (NULL);
	lst2 = NULL;
	while (lst)
	{
		filled = f(lst->content);
		if (!filled)
			ft_lstclear(&lst2, del);
		new_node = ft_lstnew(filled);
		if (!new_node)
		{
			del(filled);
			ft_lstclear(&lst2, del);
		}
		ft_lstadd_back(&lst2, new_node);
		lst = lst->next;
	}
	return (lst2);
}
