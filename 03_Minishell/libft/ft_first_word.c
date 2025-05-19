/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:53:26 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/19 14:36:35 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*count the number of chars removing the first c chars up to next c " msg"...*/
/*... will be 3*/
static size_t	word_len(char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str && str[i] && str[i] == c)
		i++;
	while (str && str[i] && str[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

/*copy the first word included the first c chars so " tomato  potato" will...*/
/*...extract " tomato" as first word*/
char	*ft_first_word(char *str, char c)
{
	char	*word;
	size_t	word_l;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	if (c == '\0')
		return (str);
	word_l = word_len(str, c);
	word = (char *)ft_calloc(word_l + 1, sizeof(char));
	if (!word)
		return (NULL);
	while (str[i] && str[i] == c)
		i++;
	while (j < word_l)
		word[j++] = str[i++];
	return (word);
}
