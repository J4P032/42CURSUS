/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:25:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/22 13:30:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../inc/minishell_j.h"

void	init_struct(t_split *squotes, char const *s, char c, size_t *i)
{
	*i = 0;
	squotes->start = 0;
	squotes->s = (char *)s;
	squotes->error = 0;
	squotes->quotes = 0;
	squotes->words = 0;
	squotes->c = c;
}

char	**ft_split_quotes2(char const *s, char c, t_input *input)
{
	size_t	i;
	char	**split;
	t_split	squotes;

	init_struct(&squotes, s, c, &i);
	squotes.words = ft_count_quotes_words(&squotes, input);
	if (squotes.error)
		return (free(input->status), NULL);
	split = (char **)ft_calloc(squotes.words + 1, sizeof(char *));
	if (!split)
		return (free(input->status), NULL);
	while (i < squotes.words)
	{
		split[i] = sub_split_quotes(&squotes, input);
		input->status[i] = input->spaced;
		if (!split[i])
		{
			while (i > 0)
				free(split[--i]);
			return (free(split), free(input->status), NULL);
		}
		i++;
	}
	return (split);
}

char	**ft_split_quotes(char const *s, char c, t_input *input)
{
	if (!s)
		return (NULL);
	else
		return (ft_split_quotes2(s, c, input));
}
