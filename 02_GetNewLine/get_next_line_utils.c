/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/28 21:40:00 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_malloc_free(t_list **list, char **content, int option)
{
	t_list	*aux;
	size_t	i;

	i = 0;
	if (option == 1)
	{
		*list = (t_list *)malloc(sizeof(t_list));
		*content = (char *)malloc(BUFFER_SIZE);
		if (!*list || !*content)
			return ;
	}
	else if (option == 0)
	{
		aux = (*list)->next;
		free(*content);
		free(*list);
		*list = aux;
	}
}


/*create new node, link it to exist list or will be the new list*/
/*returns the & of head if one only node or last node & if more than one*/
t_list	*ft_listnew(t_list **lst, void *content)
{
	t_list	*lnew;
	t_list	*aux;

	ft_malloc_free(&lnew, &content, 1);
	if (!lnew || !content)
		return (NULL);
	lnew->content = content;
	lnew->next = NULL;
	if (!*lst)
		*lst = lnew;
	else
	{
		aux = *lst;
		while (aux->next)
			aux = aux->next;
		aux->next = lnew;
	}
	return (lnew);
}


