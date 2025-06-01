/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_separator.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:21:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/09 09:53:55 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../inc/minishell_j.h"

void	init_separator(t_split *sq, size_t *i, size_t *j)
{
	*i = 0;
	*j = 0;
	if (sq->s[sq->start] == '"' && !(sq->quotes % 2))
	{
		sq->c = '"';
		(sq->quotes)++;
	}
	else if (sq->s[sq->start] == '\'' && !(sq->quotes % 2))
	{
		sq->c = '\'';
		(sq->quotes)++;
	}
	else if ((sq->s[sq->start] == '\'' || sq->s[sq->start] == '"'))
	{
		sq->c = ' ';
		(sq->quotes)++;
		(sq->start)++;
	}
}

void	run_spaces_or_one_quote(t_split *sq, t_input *input)
{
	char	letter;

	input->spaced = 0;
	if (sq->c != '"' && sq->c != '\'')
	{
		while ((sq->s[sq->start] == sq->c) && (sq->s[sq->start]))
			(sq->start)++;
	}
	else if (sq->c == '"' || sq->c == '\'')
		(sq->start)++;
	letter = sq->s[sq->start];
	assign_token_status(input, sq, letter);
}

void	open_close_quotes(t_split *sq)
{
	if (sq->s[sq->start] == '"' && !(sq->quotes % 2))
	{
		sq->c = '"';
		(sq->quotes)++;
		(sq->start)++;
	}
	else if (sq->s[sq->start] == '\'' && !(sq->quotes % 2))
	{
		sq->c = '\'';
		(sq->quotes)++;
		(sq->start)++;
	}
}

/*(sq->start)++ only when a '' or "" is found. Necesary to work ok with them*/
void	compose_split_aux(t_split *sq, size_t *i, size_t *j)
{
	while (*j < *i)
		sq->split_aux[(*j)++] = sq->s[(sq->start)++];
	if (sq->quotes % 2)
		init_separator(sq, i, j);
	if (sq->c == ' ')
	{
		while (sq->s[sq->start] && sq->s[sq->start] == sq->c)
			(sq->start)++;
	}
	sq->c = ' ';
}

char	*sub_split_quotes(t_split *sq, t_input *input)
{
	size_t	i;
	size_t	j;

	init_separator(sq, &i, &j);
	run_spaces_or_one_quote(sq, input);
	open_close_quotes(sq);
	while (sq->s[i + sq->start] && sq->s[i + sq->start] != sq->c)
	{
		if (sq->c == ' ' && (sq->s[i + sq->start] == '"'
				|| sq->s[i + sq->start] == '\''))
			break ;
		i++;
	}
	sq->split_aux = (char *)ft_calloc(i + 1, sizeof(char));
	if (!sq->split_aux)
		return (NULL);
	compose_split_aux(sq, &i, &j);
	if ((sq->c == '"' && sq->s[sq->start] == '"' && sq->s[sq->start - 1] != '"')
		|| (sq->c == '\'' && sq->s[sq->start] == '\''
			&& sq->s[sq->start - 1] != '\''))
	{
		(sq->quotes)++;
		(sq->start)++;
	}
	return (sq->split_aux);
}
