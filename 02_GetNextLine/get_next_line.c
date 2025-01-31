/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/31 11:44:44 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> ///////////////////////////

/*search for first byte with char c in first n bytes of s*/
/*if not found -> NULL*/
int	ft_find_n(const char *s, size_t n)
{
	size_t	i;
	
	i = 0;
	while (i < n)
	{
		if (s[i] == '\n')
			break ;
		i++;
	}
	if (i < n)
		return (1);
	else if (s[i] == '\n')
		return (1);
	return (0);
}

/* char	*process_last(t_list **last)
{
	ssize_t	bytes_left;
	char	*aux;
	size_t	i;
	size_t	j;

	i = 0;
	bytes_left = (*last)->read_bytes;
	aux =(char *)ft_calloc(bytes_left, 1);
	if (!aux)
		return (NULL);
	while (i < bytes_left)
	{
		if ((*last)->content[i] == '\n')
		{
			if (i != bytes_left - 1)
				i++;
			j = 0;
			while (i < bytes_left)
				aux[j++] == (*last)->content[i++];	
			free(((*last)->content));
			(*last)->content = aux;
			(*last)->read_bytes = j + 1;
			(*last)->total_rbytes = j + 1;
		}			
		i++;
	}
	return ((*last)->content);
} */
	
char	*process_last(t_list **last)
{
	ssize_t	bytes_left;
	size_t	i;
	size_t	j;

	i = 0;
	bytes_left = (*last)->read_bytes;
	while (i < bytes_left)
	{
		if ((*last)->content[i] == '\n')
		{
			j = 0;
			while (i < bytes_left - 1)
				(*last)->content[j++] = (*last)->content[++i];	
			(*last)->read_bytes = j + 1;
			(*last)->total_rbytes = j + 1;
		}			
		i++;
	}
	/* if (j == 1)
	{
		(*last)->read_bytes = 0;
		(*last)->total_rbytes = 0;
	} */
	return ((*last)->content);
} 






/*it reads a maximun of BUFFER_SIZE but realocate it not its size*/
char	*ft_read_fd(int fd, ssize_t *bytes)
{
	char	*aux;
	char	*resize;
	ssize_t	i;

	i = 0;
	aux = (char *)ft_calloc(BUFFER_SIZE, 1);
	if (!aux)
		return (NULL);
	*bytes = read(fd, aux, BUFFER_SIZE);
	resize = (char *)calloc(*bytes, 1);
	if ((*bytes <= 0) || (!resize))
	{
		free(aux);
		return (NULL);
	}
	while (i < *bytes)
	{
		resize[i] = aux[i];
		i++;
	}
	free(aux);
	return (resize);
}


char	*get_next_line(int fd)
{
	static t_list	*list;
	static t_list	*last;
	ssize_t			rbytes;
	char			*content;

	rbytes = 1;
	while(last)
	{
		process_last(&last);
		return (compose_string(&list, last));
	}
	while (rbytes > 0)
	{
		content = ft_read_fd(fd, &rbytes);
		if (!content)
			return (NULL);
		if (ft_find_n(content, rbytes))
		{
			last = ft_listnew(&list, content, rbytes);
			break ;
		}
		else
			last = ft_listnew(&list, content, rbytes);
	}
	return (compose_string(&list, last));
}
