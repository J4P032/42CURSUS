/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:19:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/13 11:37:59 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*just a 'simple' calloc to save from writing \0 lines*/
/*extra protection with sizes to 0 to return NULL*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_bytes;
	unsigned char	*ptr;
	size_t			i;

	i = 0;
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
void	free_list(t_doc **list, int option)
{
	t_doc	*aux;

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

/*first with option0 is a hack to store in 25norminette lines from GNL func*/
/*second: if finds \n in stored 'rest' in list*/
/*calloc of num of chars with \n from left of 'rest' plus 1 (so +2) for \0*/
/*process_rest with that aux(calloced). In this case 'big' is empty*/
/*finale frees are in case last data read with content reserved & list left*/
char	*give_me_rest(t_doc **l, char **content, int option, ssize_t *b)
{
	char	*aux;

	if (option == 0)
	{
		if (*b == 0 && *content)
			free(*content);
		return (NULL);
	}
	*content = NULL;
	if (!*l)
		return (NULL);
	if (findn((*l)->r_bytes, (*l)->content, 1) >= 0)
	{
		aux = (char *)ft_calloc(findn((*l)->r_bytes, (*l)->content, 1) + 2, 1);
		if (!aux)
			return (free_list(l, 1), NULL);
		return (process_rest(&aux, &((*l)->content), &((*l)->r_bytes), l));
	}
	if (*content)
		free(*content);
	if (*l && (*l)->r_bytes == 0)
		free_list(l, 1);
	return (NULL);
}

/*joins all the content of each node into one big 'line'*/
/*because rbytes and totalbytes are updated it is dynamic in calloc*/
/*once each node is passed to 'line' it just free that node and content*/
char	*compose_string(t_doc **list)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!*list)
		return (NULL);
	j = 0;
	line = (char *)ft_calloc((size_t) *(*list)->total_rbytes + 1, 1);
	if (!line)
		return (free_list(list, 1), NULL);
	while (*list)
	{
		i = 0;
		while ((i < (size_t)(*list)->r_bytes))
		{
			if (j >= (size_t) *(*list)->total_rbytes)
				return (free_list(list, 1), NULL);
			line[j] = (*list)->content[i];
			i++;
			j++;
		}
		free_list(list, 0);
	}
	return (line);
}

/*create new node, link it to exist list or will be the new list*/
/*returns the & of head if one only node or last node & if more than one*/
t_doc	*ft_listnew(t_doc **lst, char **content, ssize_t *rbytes)
{
	t_doc	*lnew;
	t_doc	*aux;

	lnew = ft_calloc(1, sizeof(t_doc));
	if (!lnew)
		return (*rbytes = 0, free(*content), *content = NULL,
			free_list(lst, 1), NULL);
	lnew->content = *content;
	lnew->r_bytes = *rbytes;
	lnew->next = NULL;
	if ((!*lst))
	{
		lnew->total_rbytes = ft_calloc(1, sizeof(ssize_t));
		if (!lnew->total_rbytes)
			return (*rbytes = 0, free(*content), *content = NULL,
				free(lnew), NULL);
		*(lnew->total_rbytes) = *rbytes;
		return (*lst = lnew, lnew);
	}
	lnew->total_rbytes = (*lst)->total_rbytes;
	*(lnew->total_rbytes) += *rbytes;
	aux = *lst;
	while (aux->next)
		aux = aux->next;
	return (aux->next = lnew, lnew);
}
