/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/03 08:31:23 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*search for first byte with char c in first n bytes of s*/
/*if not found return -1 as 0 can be a valid index */
/*if s protection needed if s=NULL (bad calloc or EOF)*/
ssize_t	findn(const char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{

		if (s && s[i] == '\n')
			return (i);
		i++;






		/* if (s && s[i] == '\n')
		{
			if (i == 0)
				return (i);
			return (i);
		}
		i++; */
	}
	return (-1);
}

char	*ft_read_fd(int fd, ssize_t *bytes, t_list **list)
{
	char	*aux;
	char	*resize;
	ssize_t	i;

	i = 0;
	aux = (char *)ft_calloc(BUFFER_SIZE + 1, 1); /////
	if (!aux)
		return (free_list(list, 1), NULL);
	*bytes = read(fd, aux, BUFFER_SIZE);
	if (*bytes == 0)
		return (free(aux), NULL);
	if (*bytes < 0)
		return (free(aux), free_list(list, 1), NULL);
	resize = (char *)ft_calloc(*bytes, 1);
	if (!resize)
		return (free(aux), free_list(list, 1), NULL);
	while (i < *bytes)
	{
		resize[i] = aux[i];
		i++;
	}
	return (free(aux), resize);
}

char	*process_last(t_list **list, t_list **last)
{
	char	*aux;

	if ((!*last))
		return (NULL);
	aux = NULL;
	aux = compose_string(list, last, aux);
	return (aux);
}

/*process first the rest of the last node in case still are bytes in it*/
/*when done the 'last' it creates a new node-list with the content readed*/
/*if finds character \n in the content readed->breaks composition of list*/
char	*get_next_line(int fd)
{
	static t_list	*list;
	static t_list	*last;
	ssize_t			rbytes;
	char			*aux_last;
	char			*content;

	rbytes = 1;
	aux_last = process_last(&list, &last);
	while ((rbytes > 0) && (!aux_last))
	{
		content = ft_read_fd(fd, &rbytes, &list);
		if ((!content) && (!list))
			return (NULL);
		if (findn(content, rbytes) >= 0)
		{
			last = ft_listnew(&list, content, rbytes);
			break ;
		}
		else if (content)
			last = ft_listnew(&list, content, rbytes);
	}
	return (compose_string(&list, &last, aux_last));
}
