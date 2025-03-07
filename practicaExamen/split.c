/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:47:03 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/06 19:02:10 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	printable(char c)
{
	if (c >=32 && c < 127)
		return 1;
	return 0;
}

int	count_words(char *str, char c)
{
	size_t	words;
	
	words = 0;
	while (*str)
	{
		while (*str && c == *str)
			str++;
		if (printable(*str))
			words++;
		while (*str && *str != c)
			str++;
	}
	return (words);
}

char	*sub_split(char *str, char c, size_t *start)
{
	char	*word = NULL;
	size_t	i = 0;
	size_t	j = 0;

	i = *start;
	while (str[i] && c == str[i])
	{
		i++;
		(*start)++;
	}
	while (str[i] && printable(str[i]) && str[i] != c)
		i++;
	word = (char*)malloc((i - *start) + 1 * sizeof(char));
	if (!word)
		return (NULL);
	while (*start < i)
	{
		word[j] = str[*start];
		(*start)++;
		j++;
	}
	word[j] = '\0';
	return (word);
}


char  **ft_split(char *str, char c)
{
	size_t	words;
	size_t	start;
	size_t	i;
	char	**solution;
	
	start = 0;
	i = 0;
	words = count_words(str, c);
	if (!words)
		return (NULL);
	solution = (char **)malloc((words + 1) * sizeof(char *));
	while (i < words)
	{
		solution[i] = sub_split(str, c, &start);
		if (!solution[i])
		{
			while (i > 0)
			{
				free(solution[i - 1]);
				solution[i - 1] = NULL;
				i--;
			}
			free(solution);
			solution = NULL;	
			return (NULL);		
		}
		i++;
	}	
	solution[i] = NULL;
	return (solution);	
}

int	main(int argc, char **argv)
{
	size_t i = 0;
	
	char	**solution = NULL;	
	if (argc != 2)
		return (0);
	solution =  ft_split(argv[1], ' ');
	if (!solution)
		return (1);

	while (solution[i])
	{
		printf("%s\n", solution[i]);
		i++;
	}
	return (0);
}
