/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/30 23:16:25 by jrollon-         ###   ########.fr       */
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
	/* if (*bytes < BUFFER_SIZE)
		resize[i] = '\0'; */
	free(aux);
	return (resize);
}


char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*last;
	ssize_t			rbytes;
	char			*content;

	rbytes = 1;
	list = NULL;
	while (rbytes > 0)
	{
		content = ft_read_fd(fd, &rbytes); //content suelta del tamaño rbytes leido
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
