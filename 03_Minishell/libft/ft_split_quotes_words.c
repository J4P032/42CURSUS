/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_words.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:45:25 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/01 12:50:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	assign_separator(t_split *squotes, size_t *i, char separator)
{
	squotes->c = separator;
	if (squotes->words % 2 == 0)
		(squotes->words)++;
	(squotes->quotes)++;
	(*i)++;
	if (squotes->words % 2 == 0)
	{
		while ((squotes->s[*i] != squotes->c) && (squotes->s[*i]))
			(*i)++;
	}
}

void	next_word_count(t_split *squotes, size_t *i)
{
	(squotes->words)++;
	while ((squotes->s[*i] != squotes->c) && (squotes->s[*i]))
	{
		(*i)++;
		if (squotes->c == ' ' && (squotes->s[*i] == '"'
				|| squotes->s[*i] == '\''))
			break ;
	}
}

int	ft_count_quotes_words(t_split *squotes)
{
	size_t	i;
	char	separator;

	if (!(squotes->s))
		return (0);
	i = 0;
	separator = squotes->c;
	while (squotes->s[i])
	{
		if (squotes->s[i] == '"' && !(squotes->quotes % 2))
			assign_separator(squotes, &i, '"');
		else if (squotes->s[i] == '\'' && !(squotes->quotes % 2))
			assign_separator(squotes, &i, '\'');
		else if (squotes->s[i] == '\'' || squotes->s[i] == '"')
			assign_separator(squotes, &i, separator);
		else if (squotes->s[i] != squotes->c)
			next_word_count(squotes, &i);
		else if (squotes->s[i])
			i++;
	}
	if (squotes->quotes % 2)
		squotes->error = 1;
	return (squotes->words);
}
