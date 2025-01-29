/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/29 18:23:15 by jrollon-         ###   ########.fr       */
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
		if (!*list)
			return ;
	}
	else if (option == 0)
	{
		aux = (*list)->next;
		free(*content);
		(*content) = NULL;
		free(*list);
		*list = aux;
	}
}

char	*compose_string(t_list *list)
{
	char	*line;
	size_t	i;
	size_t	node;

	node = 0;
	line = (char *)malloc(*(list->num_nodes) * BUFFER_SIZE);
	if (!line)
		return (NULL);
	while (list)
	{
		i = 0;
		while ((i < BUFFER_SIZE) && (list->content[i] != '\n'))
		{
			line[i + (BUFFER_SIZE * node)] = list->content[i];
			i++;
		}
		if (list->content[i] == '\n')
			line[i + (BUFFER_SIZE * node)] = '\n';
		line[++i + (BUFFER_SIZE * node)] = '\0';
		node++;
		ft_malloc_free(&list, &(list->content), 0);
	}
	return (line);
}

/*create new node, link it to exist list or will be the new list*/
/*returns the & of head if one only node or last node & if more than one*/
t_list	*ft_listnew(t_list **lst, char *content)
{
	t_list			*lnew;
	t_list			*aux;
	static int		num_nodes;

	num_nodes = 0;
	ft_malloc_free(&lnew, &content, 1);
	if (!lnew || !content)
		return (NULL);
	lnew->content = content;
	lnew->num_nodes = &num_nodes;
	lnew->next = NULL;
	num_nodes++;
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
