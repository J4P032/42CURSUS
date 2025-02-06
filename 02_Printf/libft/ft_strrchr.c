/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:42:05 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/19 09:57:18 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*Finds char c inside of string s*/
/*if found -> returns pointer to LAST found in s*/
/*not found -> NULL*/
/*c = '\0' returns the first terminator*/
/*needs to cast (char) because overflow conversion c = 1024 = \0
	c = 'e'+256 = 'e'*/
/*(char *) because it is a non const return from const char* */
char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	last;
	int		found;

	i = 0;
	last = 0;
	found = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			last = i;
			found = 1;
		}
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	else if (found)
		return ((char *)&s[last]);
	return (NULL);
}
