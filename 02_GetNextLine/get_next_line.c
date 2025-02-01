/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/01 22:13:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	else if (s && s[i] == '\n')
		return (1);
	return (0);
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
	if (*bytes > 0)
		resize = (char *)ft_calloc(*bytes, 1);
	if ((*bytes <= 0) || (!resize))
	{
		free(aux);
		free(resize);
		return (NULL);
	}
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
		content = ft_read_fd(fd, &rbytes);
		if ((!content) && (!list))
			return (NULL);
		if (ft_find_n(content, rbytes))
		{
			last = ft_listnew(&list, content, rbytes);
			break ;
		}
		else if (content)
			last = ft_listnew(&list, content, rbytes);
	}
	return (compose_string(&list, &last, aux_last));
}
