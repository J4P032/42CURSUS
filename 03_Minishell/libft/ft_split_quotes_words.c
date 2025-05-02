/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_words.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:45:25 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/02 17:13:49 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../inc/minishell_j.h" //javi

/*Important to set finale c to space for quote count words do it propertly*/
void	assign_separator(t_split *squotes, size_t *i, char separator)
{
	squotes->c = separator;
	if (squotes->quotes % 2 == 0)
		(squotes->words)++;
	(squotes->quotes)++;
	(*i)++;
	while (squotes->s[*i] && squotes->s[*i] != squotes->c)
		(*i)++;
	if (squotes->s[*i] == squotes->c)
	{
		(squotes->quotes)++;
		(*i)++;
	}
	squotes->c = ' ';
}

void	next_word_count(t_split *squotes, size_t *i)
{
	(squotes->words)++;
	while (squotes->s[*i] && squotes->s[*i] != squotes->c)
	{
		(*i)++;
		if (squotes->c == ' ' && (squotes->s[*i] == '"'
				|| squotes->s[*i] == '\''))
			break ;
	}
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
	input->is_spaced = 0;
	input->spaced = (int *)ft_calloc(squotes->words, sizeof(int));
	if (!input->spaced)
		squotes->error = 1;
	return (squotes->words);
}
