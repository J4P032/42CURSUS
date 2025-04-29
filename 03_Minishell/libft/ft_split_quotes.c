/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:25:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/29 09:13:00 by jrollon-         ###   ########.fr       */
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
	if (quotes % 2)
		*error = 1;
	return (words);
}

/*1.run all s through c chars to remove them with (*start)++*/
/*2.count each letter until I find a c char with i*/
/*3.ft_calloc of i + 1 elements of each string*/
/*4.return to start and form the string from start to i*/
/*(*start) will be updated to new position to be send back to split*/
static char	*sub_split(char const *s, char *c, size_t *start, int *quotes)
{
	size_t	i;
	size_t	j;
	char	*split_aux;
	
	i = 0;
	j = 0;

	if (s[*start] == '"' && !(*quotes % 2))
	{
		*c = '"';
		(*quotes)++;
	}
	else if (s[*start] == '\'' && !(*quotes % 2))
	{
		*c = '\'';
		(*quotes)++;
	}
	else if (s[*start] == '\'' || s[*start] == '"')
	{
		*c = ' ';
		(*quotes)++;
		(*start)++;
	}

	if (*c != '"' && *c != '\'')
	{
		while ((s[*start] == *c) && (s[*start]))
			(*start)++;
	}
	else if (*c == '"' || *c == '\'')
		(*start)++;
	

	if (s[*start] == '"' && !(*quotes % 2))
	{
		*c = '"';
		(*quotes)++;
		(*start)++;
	}
	else if (s[*start] == '\'' && !(*quotes % 2))
	{
		*c = '\'';
		(*quotes)++;
		(*start)++;
	}
	else if (*c == '"' && s[*start] == '"')
	{
		(*quotes)++;
		(*start)++;
	}
	else if (*c == '\'' && s[*start] == '\'')
	{
		(*quotes)++;
		(*start)++;
	}

	

	while (s[i + *start] && s[i + *start] != *c)
		i++;

		
	split_aux = (char *)ft_calloc(i + 1, sizeof(char));
	if (!split_aux)
		return (NULL);
	while (j < i)
		split_aux[j++] = s[(*start)++];

	if (*c == ' ')
	{
		while (s[*start] && s[*start] == *c)
			(*start)++;
	}
		
	*c = ' ';
	

	return (split_aux);
}

char	**ft_split_quotes(char const *s, char c, int *error, int *words)
{
	//size_t	words;
	size_t	i;
	size_t	start;
	char	**split;
	int		quotes;

	i = 0;
	start = 0;
	quotes = 0;
	*words = ft_count_words((char *)s, c, error);
	if (*error)
		return NULL;
	split = (char **)ft_calloc(*words + 1, sizeof(char *));
	if (!split)
		return (NULL);
	while (i < *words)
	{
		split[i] = sub_split(s, &c, &start, &quotes);
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

#include <stdio.h>
int main (void)
{
	//char	*kk = "\"echo \"   \"   \"\"\"\"'\"'\"' hola";
	char	*kk = "\"\"\"'\"'\"' hola";
	
	size_t	i = 0;
	int		number = 0;
	int		words;
	words = 0;
	char 	**solucion = ft_split_quotes(kk, ' ', &number, &words);	
	
	while (i < words)
	{
		printf("%s\n", solucion[i]);
		free (solucion[i]);
		i++;
	}
	return 0;	
}
