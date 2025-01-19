/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:17:39 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/19 09:56:02 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*Finds char c inside of string s*/
/*if found -> returns pointer to first found in s*/
/*not found -> NULL*/
/*c = '\0' returns the first terminator*/
/*needs to cast (char) because overflow conversion c = 1024 = \0
	c = 'e'+256 = 'e'*/
/*(char *) because it is a non const return from const char* */
char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	else
		return (NULL);
}
