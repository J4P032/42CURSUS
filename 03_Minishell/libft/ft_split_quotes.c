/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:25:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/02 19:34:25 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../inc/minishell_j.h"

void	clean_nulls(char ***split, t_split *squotes, int **spaced)
{
	size_t	i;
	size_t	j;
	char	**aux;
	int		*numbers;

	i = 0;
	j = 0;
	aux = *split;
	numbers = *spaced;
	while (i < squotes->words)
	{
		if (aux[i] && aux[i][0] != '\0')
		{
			(*spaced)[j] = numbers[i];
			(*split)[j++] = aux[i];
		}
		else
			free (aux[i]);
		i++;
	}
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
		return (free(input->spaced), NULL);//mirar que free bien el malloc de spaced
	while (i < squotes.words)
	{
		split[i] = sub_split_quotes(&squotes, input);
		input->spaced[i] = input->is_spaced;
		if (!split[i])
		{
			while (i > 0)
				free(split[--i]);
			return (free(split), NULL);
		}
		i++;
	}
	clean_nulls(&split, &squotes, &(input->spaced));
	return (split);
}

/* #include <stdio.h>
int main (void)
{
	//char	*kk = "\"echo\"   \"   \"\"\"\"'\"'\"'  hola";
	//char	*kk = "\"\"\"'\"'\"' hola";
	//char *kk = "\"\"\"\"echo \"patata ''' de ayer   ya!!\"";
	char *kk = "echo\"patata\"     tomate    ";
	
	//char *kk = "\"echo\"   \"patata 'lechuga'\"    tomate"; //este mal

	size_t	i = 0;
	int		error = 0;
	int		words;
	words = 0;
	char 	**solucion = ft_split_quotes(kk, ' ', &error, &words);	
	if (error)
	{
		printf("error");
		return (1);
	}
	while (i < words)
	{
		printf("%s", solucion[i]);
		free (solucion[i]);
		i++;
	}
	return 0;	
} */
