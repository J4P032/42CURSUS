/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/29 22:32:42 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*	1.Read in main from argv[1] data from terminal or file.txt*/
/*	2.Read with BUFFER_SIZE with two possibilities: */
/*		a.BUFFER_SIZE < size of the document*/
/*		b.BUFFER_SIZE >= size the document */
/*	3. if case (b): */
/*		- Split the buffer with separator \n or EOF to return full line */
/*	4. if case (a): */
/*		- Store the read buffer in a node of a list */
/*		- if \n || EOF found store the rest after in an static var	*/
/*		- run the list up to the \n or EOF and STRJOIN all into a full STR */
/*	5.Free the list after processing the line */
/*	6.Start a new list for nextline addign first the static one */
/*	Can be done with while inside GNL up to find \n or every fill of BUFFER */

/*search for first byte with char c in first n bytes of s*/
/*if not found -> NULL*/
int	ft_find_n(char *rest, const char *s, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < n)
	{
		if (s[i] == '\n')
			break ;
		i++;
	}
	if (i < n - 1)
	{
		while (i < n)
			rest[j++] = s[++i];
		rest[j] = '\0';
		return (1);
	}
	else if (s[n - 1] == '\n')
	{
		rest[0] = '\n';
		return (1);
	}
	return (0);
}

void	process_rest(t_list *list, char **rest)
{
	char	*aux;
	size_t	i;

	i = 0;
	aux = (char *)malloc(BUFFER_SIZE + 1);
	while ((*rest[i]) || (i < BUFFER_SIZE ))
	{
		aux[i] = *rest[i];
		i++;
	}
	aux[i] = '\0';
	free(*rest);
	*rest = aux;
	if (*rest && *rest[0] != '\0')
	ft_listnew(&list, *rest);
}

char	*ft_read_fd(int fd, int *bytes)
{
	char	*aux;

	aux = (char *)malloc(BUFFER_SIZE);
	if (!aux)
		return (NULL);
	*bytes = read(fd, aux, BUFFER_SIZE);
	if (*bytes <= 0)
	{
		free(aux);
		aux = NULL;
		return (NULL);
	}
	return (aux);
}

/*I need to reserve memory to give the first read to content*/
char	*get_next_line(int fd)
{
	t_list		*list;
	int			rbytes;
	char		*content;
	static char	*rest;

	rbytes = 1;
	list = NULL;
	rest = NULL;
	ft_malloc_free(&list, &rest, 2);
	while (rbytes > 0)
	{
		process_rest(list, &rest);
		content = ft_read_fd(fd, &rbytes);
		if (ft_find_n(rest, content, rbytes) && content)
		{
			ft_listnew(&list, content);
			break ;
		}
		else if (content)
			ft_listnew(&list, content);
	}
	return (compose_string(list));
}
