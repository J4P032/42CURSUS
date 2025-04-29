/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_separator.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:21:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/29 18:11:08 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_separator(t_split *squotes, size_t *i, size_t *j, size_t *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
	if (squotes->s[squotes->start] == '"' && !(squotes->quotes % 2))
	{
		squotes->c = '"';
		(squotes->quotes)++;
	}
	else if (squotes->s[squotes->start] == '\'' && !(squotes->quotes % 2))
	{
		squotes->c = '\'';
		(squotes->quotes)++;
	}
	else if (squotes->s[squotes->start] == '\''
		|| squotes->s[squotes->start] == '"')
	{
		squotes->c = ' ';
		(squotes->quotes)++;
		(squotes->start)++;
	}
}

void	run_spaces_or_one_quote(t_split *squotes, size_t *k)
{
	if (squotes->c != '"' && squotes->c != '\'')
	{
		while ((squotes->s[squotes->start] == squotes->c)
			&& (squotes->s[squotes->start]))
			(squotes->start)++;
	}
	else if (squotes->c == '"' || squotes->c == '\'')
	{
		if (squotes->quotes % 2 && squotes->s[(squotes->start) - 1] == ' ')
			*k = 1;
		(squotes->start)++;
	}
}

void	open_close_quotes(t_split *squotes)
{
	if (squotes->s[squotes->start] == '"' && !(squotes->quotes % 2))
	{
		squotes->c = '"';
		(squotes->quotes)++;
		(squotes->start)++;
	}
	else if (squotes->s[squotes->start] == '\'' && !(squotes->quotes % 2))
	{
		squotes->c = '\'';
		(squotes->quotes)++;
		(squotes->start)++;
	}
	else if (squotes->c == '"' && squotes->s[squotes->start] == '"')
	{
		(squotes->quotes)++;
		(squotes->start)++;
	}
	else if (squotes->c == '\'' && squotes->s[squotes->start] == '\'')
	{
		(squotes->quotes)++;
		(squotes->start)++;
	}
}

/*k is for inserting an space in certain cases that are spaces before or...*/
/*...after the previus word with*/
void	compose_split_aux(t_split *squotes, size_t *i, size_t *j, size_t *k)
{
	while (*j < *i + *k)
	{
		if (*j == 0 && *k == 1)
			squotes->split_aux[(*j)++] = ' ';
		else
			squotes->split_aux[(*j)++] = squotes->s[(squotes->start)++];
	}
	if (squotes->c == ' ')
	{
		while (squotes->s[squotes->start]
			&& squotes->s[squotes->start] == squotes->c)
			(squotes->start)++;
	}
	squotes->c = ' ';
}

/*normal split*/
/*1.run all s through c chars to remove them with (*start)++*/
/*2.count each letter until I find a c char with i*/
/*3.ft_calloc of i + 1 elements of each string*/
/*4.return to start and form the string from start to i*/
/*(*start) will be updated to new position to be send back to split*/
/*k is for inserting an space in certain cases that are spaces before or...*/
/*...after the previus word with*/
char	*sub_split_quotes(t_split *squotes)
{
	size_t	i;
	size_t	j;
	size_t	k;

	init_separator(squotes, &i, &j, &k);
	run_spaces_or_one_quote(squotes, &k);
	open_close_quotes(squotes);
	if (squotes->quotes > 0 && squotes->quotes % 2 == 0
		&& squotes->c == ' ' && squotes->s[(squotes->start) - 1] == ' ')
		k = 1;
	while (squotes->s[i + squotes->start]
		&& squotes->s[i + squotes->start] != squotes->c)
	{
		if (squotes->c == ' ' && (squotes->s[i + squotes->start] == '"'
				|| squotes->s[i + squotes->start] == '\''))
			break ;
		i++;
	}
	squotes->split_aux = (char *)ft_calloc(i + k + 1, sizeof(char));
	if (!squotes->split_aux)
		return (NULL);
	compose_split_aux(squotes, &i, &j, &k);
	return (squotes->split_aux);
}
