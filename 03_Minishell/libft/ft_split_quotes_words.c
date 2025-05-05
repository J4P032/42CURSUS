/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_words.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:45:25 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/05 10:11:36 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../inc/minishell_j.h"

void	next_word_count(t_split *squotes, size_t *i)
{
	if (squotes->s[*i] != '"' && squotes->s[*i] != '\'')//
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
	int	escaped;
	
	escaped = is_escaped(sq, *i);
	if (escaped)
	{
		next_word_count(sq, i);
		return ;	
	}		
	sq->c = separator;
	if (sq->quotes % 2 == 0 && !escaped)
		(sq->words)++;
	if (!escaped)
		(sq->quotes)++;
	(*i)++;
	while (sq->s[*i] && (sq->s[*i] != sq->c || is_escaped(sq, *i)))
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
		squotes->error = 1;
	squotes->quotes = 0;
	input->status = (int *)ft_calloc(squotes->words, sizeof(int));
	if (!input->status)
		squotes->error = 1;
	input->input_words = squotes->words;
	return (squotes->words);
}
