/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:17:39 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/09 22:16:55 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr_quotes(const char *s, int c)
{
	size_t	i;
	size_t	quotes;
	size_t	double_quotes;

	i = 0;
	quotes = 0;
	double_quotes = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			quotes++;
		else if (s[i] == '"')
			double_quotes++;
		if (s[i] == (char)c && quotes % 2 == 0 && double_quotes % 2 == 0)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	else
		return (NULL);
}
