/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/13 11:36:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*this function do 2 things depending on option*/
/*option1:search for index of \n. if not found returns -1 (ssize_t)*/
/*option0:makes an strlen*/
ssize_t	findn(size_t n, const char *s, int option)
{
	size_t	i;

	i = 0;
	if (option == 1)
	{
		if (!s)
			return (-1);
		while (i < n)
		{
			if (s && s[i] == '\n')
				return (i);
			i++;
		}
		return (-1);
	}
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

/*reads from open fd and insert it in aux with BUFFER_SIZE*/
/*if bytes read (that is modified by pointer) != BUFFER_SIZE...*/
/*it 'realoc' it into resize to better memory management*/
char	*ft_read_fd(int fd, ssize_t *bytes, t_doc **list)
{
	char	*aux;
	char	*resize;
	ssize_t	i;

	i = 0;
	aux = (char *)ft_calloc(BUFFER_SIZE, 1);
	if (!aux)
		return (*bytes = 0, free_list(list, 1), NULL);
	*bytes = read(fd, aux, BUFFER_SIZE);
	if (*bytes == 0)
		return (free(aux), NULL);
	if (*bytes < 0)
		return (free(aux), free_list(list, 1), NULL);
	if (*bytes == BUFFER_SIZE)
		return (aux);
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

/*joins source and rest into dest with correct size*/
/*it does it if both exists in one pass*/
char	*str_join(char *dest, char *src, char *rest, ssize_t length)
{
	ssize_t	i;
	ssize_t	src_len;

	i = -1;
	src_len = findn(0, src, 0);
	if (!src && !rest)
		return (NULL);
	if (!src || !rest)
	{
		if (!rest)
			return (src);
		while (++i < length)
			dest[i] = rest[i];
		return (dest);
	}
	i = 0;
	while (i < src_len || i < length)
	{
		if (i < src_len)
			dest[i] = src[i];
		if (i < length)
			dest[i + src_len] = rest[i];
		i++;
	}
	return (dest);
}

/*joins 'big' data from list nodes without \n with up to first \n in rest*/
/*line 119: moves from back to front of the rest after /n*/
/*updates bytes of node & totalbytes of whole list with the rest to process*/
char	*process_rest(char **big, char **rest, ssize_t *rbytes, t_doc **lst)
{
	ssize_t	i;
	size_t	j;
	ssize_t	big_length;
	ssize_t	rest_length;
	char	*aux;

	big_length = findn(0, *big, 0);
	rest_length = 0;
	if ((*rbytes > 0) && (findn(*rbytes,*rest, 1) >= 0))
		rest_length = findn(*rbytes, *rest, 1) + 1;
	aux = (char *)ft_calloc(big_length + rest_length + 1, 1);
	if (!aux)
		return (free(*rest), *rest = NULL, free(*big), free_list(lst, 1), NULL);
	aux = str_join(aux, *big, *rest, rest_length);
	if (*big)
		free(*big);
	i = 0;
	j = rest_length;
	while (i < *rbytes - rest_length)
		(*rest)[i++] = (*rest)[j++];
	(*rest)[i] = '\0';
	*rbytes -= rest_length;
	if ((*lst) && ((*lst)->total_rbytes))
		*((*lst)->total_rbytes) -= rest_length;
	return (aux);
}

/*give_me_rest: gives the string of chars up to first \n*/
/*content: Function that reads the number of bytes. updated by pointer*/
/*if find the \n in content it dont store it in list but join it with big*/
/*rest of 'rest' with or not \n chars is stored in a new first head node*/
/*give_me_rest in middle is a hack to free last content without bytes readed*/
/*if not found in 'content' any \n char then directly stores in list*/
char	*get_next_line(int fd)
{
	static t_doc	*list;
	ssize_t			rbytes;
	char			*content;
	char			*big;

	rbytes = 1;
	big = give_me_rest(&list, &content, 1, &rbytes);
	while (rbytes > 0 && (!big))
	{
		content = ft_read_fd(fd, &rbytes, &list);
		if ((!content) && (list))
			return (big = compose_string(&list), free_list(&list, 1), big);
		if (findn(rbytes, content, 1) >= 0)
		{
			big = compose_string(&list);
			big = process_rest(&big, &content, &rbytes, &list);
			if (content && rbytes > 0 && big)
				ft_listnew(&list, &content, &rbytes);
			give_me_rest(&list, &content, 0, &rbytes);
			return (big);
		}
		else if (content)
			ft_listnew(&list, &content, &rbytes);
	}
	return (big);
}
