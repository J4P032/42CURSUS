/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/31 22:36:29 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_bytes;
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > (size_t)-1 / size)
		return (NULL);
	total_bytes = nmemb * size;
	ptr = (unsigned char *)malloc(total_bytes);
	if (!ptr)
		return (NULL);
	while (i < total_bytes)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}


void	free_list(t_list **list, t_list **last)
{
	t_list	*aux;
	
	aux = (*list)->next;
	free((*list)->content);
	(*list)->content = NULL;
	(*list)->read_bytes = 0;
	(*list)->total_rbytes = 0;
	(*list)->next = NULL;
	free(*list);
	*list = aux;
	if ((*last) && (*last)->total_rbytes == 0)
	{
		//free((*last)->content);
		//(*last)->content = NULL;
		//(*last)->read_bytes = 0;
		//(*last)->total_rbytes = 0;
		//(*last)->next = NULL;
		//free(*last);
		*last = NULL;	
	}
}


void	copy_content(char *line, t_list *node, t_list *last, size_t node_i)
{
	size_t	j;
	size_t	i;
	
	j = 0;
	i = 0;
	while ((i < (size_t)node->read_bytes) && (node->content[i] != '\n'))
	{
		line[i + (BUFFER_SIZE * node_i)] = node->content[i];
		i++;
	}
	if (node->content[i] == '\n')
			line[i + (BUFFER_SIZE * node_i)] = '\n';
	while (i < (size_t)node->read_bytes - 1)
		node->content[j++]	= node->content[++i];
	i = 0;
	while (line[i])
		i++;
	node->read_bytes = node->read_bytes - i;
	last->total_rbytes -= i;
}


char	*compose_string(t_list **list, t_list **last, char *aux_last)
{
	char	*line;
	size_t	node;

	if (aux_last) ///pasar hackear la salida del ultimo nodo
		return (aux_last);
	if (!*list)
		return (NULL);
	node = 0;
	line = (char *)ft_calloc(((*last)->total_rbytes) + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (*list)
	{
		copy_content(line, *list, *last, node);///
		node++;
		if (((*last)->read_bytes > 0) && (*list == *last))
			break ;
		free_list(list, last);
	}
	return (line);
}

/*create new node, link it to exist list or will be the new list*/
/*returns the & of head if one only node or last node & if more than one*/
t_list	*ft_listnew(t_list **lst, char *content, ssize_t rbytes)
{
	t_list			*lnew;
	t_list			*aux;
	static ssize_t	total_rbytes;
	
	if (!*lst)
		total_rbytes = 0;
	lnew = ft_calloc(1, sizeof(t_list));
	if (!lnew || !content)
		return (NULL);
	lnew->content = content;
	lnew->read_bytes = rbytes;
	lnew->total_rbytes = total_rbytes + rbytes;
	lnew->next = NULL;
	total_rbytes+= rbytes;
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
