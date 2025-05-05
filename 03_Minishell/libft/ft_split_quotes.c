/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:25:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/05 13:59:58 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../inc/minishell_j.h"

void	clean_nulls(char ***split, t_split *squotes, int **status)
{
	size_t	i;
	size_t	j;
	char	**aux;
	int		*numbers;

	i = 0;
	j = 0;
	aux = *split;
	numbers = *status;
	while (i < squotes->words)
	{
		if (aux[i] && aux[i][0] != '\0')
		{
			(*status)[j] = numbers[i];
			(*split)[j++] = aux[i];
		}
		else
			free (aux[i]);
		//printf("%s: %d\n", aux[i], numbers[i]);//
		i++;
	}
	//printf("--------\n");
	(*split)[j] = NULL;
	squotes->words = j;
}

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

char	**ft_split_quotes(char const *s, char c, t_input *input)
{
	size_t	i;
	char	**split;
	t_split	squotes;

	init_struct(&squotes, s, c, &i);
	squotes.words = ft_count_quotes_words(&squotes, input);
	if (squotes.error)
		return (NULL);
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
			return (free(split), NULL);
		}
		i++;
	}
	//clean_nulls(&split, &squotes, &(input->status));
	return (split);
}
