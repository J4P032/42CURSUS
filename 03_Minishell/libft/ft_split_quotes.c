/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:25:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/28 18:49:33 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char *s, char c, int *error)
{
	size_t	i;
	size_t	words;
	int		quotes;
	char	separator;
	
	if (!s)
		return (0);
	i = 0;
	words = 0;
	quotes = 0;
	separator = c;
	while (s[i])
	{
		if (s[i] == '"' && !(quotes % 2))
		{
			c = '"';
			words++;
			quotes++;
			i++;
			while ((s[i] != c) && (s[i]))
				i++;
		}
		else if (s[i] == '\'' && !(quotes % 2))
		{
			c = '\'';
			words++;
			quotes++;
			i++;
			while ((s[i] != c) && (s[i]))
				i++;
		}
		else if (s[i] == '\'' || s[i] == '"')
		{
			c = separator;
			quotes++;
			i++;
		}
	
		
		else if (s[i] != c)
		{
			words++;
			while ((s[i] != c) && (s[i]))
				i++;
		}
		else if (s[i])
			i++;
	}
	if (!(quotes % 2))
		*error = 1;
	return (words);
}

/*1.run all s through c chars to remove them with (*start)++*/
/*2.count each letter until I find a c char with i*/
/*3.ft_calloc of i + 1 elements of each string*/
/*4.return to start and form the string from start to i*/
/*(*start) will be updated to new position to be send back to split*/
static char	*sub_split(char const *s, char *c, size_t *start)
{
	size_t	i;
	size_t	j;
	char	*split_aux;

	i = 0;
	j = 0;

	while ((s[*start] == *c) && (s[*start]))
		(*start)++;
	
	if (s[*start] == '"')
		*c = '"';
	else if (s[*start] == '\'')
		*c = '\'';
	
	if ((s[*start] == *c) && (s[*start]))
		(*start)++;
	
	while (s[i + *start] && s[i + *start] != *c)
		i++;
	split_aux = (char *)ft_calloc(i + 1, sizeof(char));
	if (!split_aux)
		return (NULL);
	while (j < i)
		split_aux[j++] = s[(*start)++];
	return (split_aux);
}

char	**ft_split_quotes(char const *s, char c, int *error)
{
	size_t	words;
	size_t	i;
	size_t	start;
	char	**split;

	i = 0;
	start = 0;
	words = ft_count_words((char *)s, c, error);
	if (*error)
		return NULL;
	split = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!split)
		return (NULL);
	while (i < words)
	{
		split[i] = sub_split(s, &c, &start);
		if (!split[i])
		{
			while (i > 0)
				free(split[--i]);
			free(split);
			return (NULL);
		}
		i++;
	}
	return (split);
}
