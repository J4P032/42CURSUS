/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_separator.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:21:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/02 18:46:14 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../inc/minishell_j.h" //javi

void	init_separator(t_split *squotes, size_t *i, size_t *j)
{
	*i = 0;
	*j = 0;
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

void	run_spaces_or_one_quote(t_split *squotes, t_input *input)
{
	input->is_spaced = 0;
	if (squotes->start != 0 && squotes->s[(squotes->start) - 1] == ' ')
		input->is_spaced = 1;
	if (squotes->c != '"' && squotes->c != '\'')
	{
		while ((squotes->s[squotes->start] == squotes->c)
			&& (squotes->s[squotes->start]))
			(squotes->start)++;
		if (squotes->start != 0 && squotes->s[(squotes->start) - 1] == ' ')
			input->is_spaced = 1;
	}
	else if (squotes->c == '"' || squotes->c == '\'')
		(squotes->start)++;
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
		(squotes->quotes)++;
	else if (squotes->c == '\'' && squotes->s[squotes->start] == '\'')
		(squotes->quotes)++;
}

/*k is for inserting an space in certain cases that are spaces before or...*/
/*...after the previus word with*/
void	compose_split_aux(t_split *squotes, size_t *i, size_t *j)
{
	while (*j < *i)
		squotes->split_aux[(*j)++] = squotes->s[(squotes->start)++];
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
char	*sub_split_quotes(t_split *sq, t_input *input)
{
	size_t	i;
	size_t	j;

	init_separator(sq, &i, &j);
	run_spaces_or_one_quote(sq, input);
	open_close_quotes(sq);
	/* if (sq->quotes > 0 && sq->quotes % 2 == 0
		&& sq->c == ' ' && sq->s[(sq->start) - 1] == ' ')
		input->is_spaced = 1; */
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
	if ((sq->c == '"' && sq->s[sq->start] == '"')
		|| (sq->c == '\'' && sq->s[sq->start] == '\''))
		(sq->start)++;
	compose_split_aux(sq, &i, &j);
	return (sq->split_aux);
}
