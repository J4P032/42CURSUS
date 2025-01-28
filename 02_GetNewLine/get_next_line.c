/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/28 17:55:42 by jrollon-         ###   ########.fr       */
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
char	*ft_find_n(char *rest, const char *s, size_t n)
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
		return (rest);
	}
	else if (s[n - 1] == '\n')
	{
		rest[0] = '\n';
		return (rest);
	}
	else if (s[n - 1] != '\n')
		return (NULL);
}

char	*get_next_line(int fd)
{
	t_list		*list;
	char		*content;
	size_t		rbytes;
	static char	*rest;

	list = NULL;
	content = NULL;
	if (!rest)
		rest = (char *)malloc(BUFFER_SIZE);
	ft_malloc_free(&list, &content, 1);
	list->content = content;
	rbytes = read(fd, list->content, BUFFER_SIZE);
	while (rbytes > 0)
	{
		ft_find_n(rest, list->content, rbytes);
		if (rest)
		{
			funcion que haga esto por que me paso de norminette:
			compon la lista con strjoin
			//almacena el resto despues de \n en posicion ft_strchr + 1 en static
			rest = ft
			return lo compuesto por strjoin
		}
		else
			ft_listnew(&list, &content);
	}
}







/*
char	*ft_strjoin(char const *s1, char const *s2) para juntarlo


*/
