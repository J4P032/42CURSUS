/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_words.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:45:25 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/07 12:04:52 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../inc/minishell_j.h"

void	next_word_count(t_split *squotes, size_t *i)
{
	if (squotes->s[*i] != '"' && squotes->s[*i] != '\'')
		(squotes->words)++;
	while (squotes->s[*i] && squotes->s[*i] != squotes->c)
	{
		(*i)++;
		if (squotes->c == ' ' && (squotes->s[*i] == '"'
				|| squotes->s[*i] == '\''))
			break ;
	}
}

/* Important: set final c to space so word count works properly with quotes */
void	assign_separator(t_split *sq, size_t *i, char separator)
{
	sq->c = separator;
	if (sq->quotes % 2 == 0)
		(sq->words)++;
	(sq->quotes)++;
	(*i)++;
	while (sq->s[*i] && (sq->s[*i] != sq->c))
		(*i)++;
	if (sq->s[*i] == sq->c)
	{
		(sq->quotes)++;
		(*i)++;
	}
	sq->c = ' ';
}

int	ft_count_quotes_words(t_split *squotes, t_input *input)
{
	size_t	i;

	if (!squotes->s)
		return (0);
	i = 0;
	while (squotes->s[i])
	{
		if (squotes->s[i] == '"')
			assign_separator(squotes, &i, '"');
		else if (squotes->s[i] == '\'')
			assign_separator(squotes, &i, '\'');
		else if (squotes->s[i] != squotes->c)
			next_word_count(squotes, &i);
		else if (squotes->s[i])
			i++;
	}
	if (squotes->quotes % 2)
		return (squotes->error = 1, 0);
	squotes->quotes = 0;
	input->status = (int *)ft_calloc(squotes->words, sizeof(int));
	if (!input->status)
		squotes->error = 1;
	input->input_words = squotes->words;
	return (squotes->words);
}
