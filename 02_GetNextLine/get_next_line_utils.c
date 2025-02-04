/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/04 20:50:27 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

 void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_bytes;
	unsigned char	*ptr;
	size_t			i;

	i = 0;
/* 	static int count; ///////////
	count++;
	if (count == 4)
		return (NULL);/////// */
 	if (nmemb == 0 || size == 0)
		return (NULL);
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

/*with option 1 removes all the list in case of error*/
/*with other 'option' it just removes the node worked*/
void	free_list(t_list **list, int option)
{
	t_list	*aux;

	if (!*list)
		return ;
	if (option == 1)
	{
		while (*list)
		{
			aux = (*list)->next;
			free((*list)->content);
			if (!aux)
				free ((*list)->total_rbytes);
			free(*list);
			*list = aux;
		}
		return ;
	}
	aux = (*list)->next;
	free((*list)->content);
	(*list)->content = NULL;
	if (!(*list)->next)
		free ((*list)->total_rbytes);
	(*list)->next = NULL;
	free(*list);
	*list = aux;
}

char	*give_me_rest(t_list **list)
{
	char	*aux;
	ssize_t	rest_length;

	if (!*list)
		return (NULL);
	rest_length = 0;
	if (findn((*list)->r_bytes, (*list)->content, 1) >= 0)
	{
		rest_length = findn((*list)->r_bytes, (*list)->content, 1) + 1;
		aux = (char *)ft_calloc(rest_length + 1, 1);
		if (!aux)
			return (free_list(list, 1), NULL);
		aux = process_rest(&aux, (*list)->content, &((*list)->r_bytes), list);
		return (aux);
	}
	rest_length = (*list)->r_bytes;
	aux = (char *)ft_calloc(rest_length + 1, 1);
	if (!aux)
		return (free_list(list, 1), NULL);
	aux = str_join(aux, NULL, (*list)->content, (*list)->r_bytes);
	return (aux);  //si no encuentra \n pero hay lista pasamos NULL para que pase dentro del while

	//return (aux);
}

char	*compose_string(t_list **list)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!*list)
		return (NULL);
	j = 0;
	line = (char *)ft_calloc((size_t)*(*list)->total_rbytes + 1, 1);
	if (!line)
		return (free_list(list, 1), NULL);

	while (*list)
	{
		i = 0;
		while ((i < (size_t)(*list)->r_bytes))
		{
			if (j >= (size_t)*(*list)->total_rbytes) // Protección
            	return (free_list(list, 1), NULL);
        	line[j] = (*list)->content[i]; // Copia en orden
        i++;
        j++;
		}
		free_list(list, 0);//solo limpia un nodo y pasa al siguiente
	}
	return (line);
}

/*create new node, link it to exist list or will be the new list*/
/*returns the & of head if one only node or last node & if more than one*/
t_list	*ft_listnew(t_list **lst, char *content, ssize_t rbytes)
{
	t_list	*lnew;
	t_list	*aux;

	lnew = ft_calloc(1, sizeof(t_list));
	if (!lnew)
		return (free_list(lst, 1), NULL);   //liberacion total de lista
	lnew->content = content;
	lnew->r_bytes = rbytes;
	lnew->next = NULL;
	if ((!*lst))
	{
		lnew->total_rbytes = ft_calloc(1, sizeof(ssize_t));
		if (!lnew->total_rbytes)
			return (free(lnew), free_list(lst, 1), NULL);
		*(lnew->total_rbytes) = rbytes;
		return (*lst = lnew, lnew);
	}
	lnew->total_rbytes = (*lst)->total_rbytes;
	*(lnew->total_rbytes) += rbytes;
	aux = *lst;
	while (aux->next)
		aux = aux->next;
	return (aux->next = lnew, lnew);
}
