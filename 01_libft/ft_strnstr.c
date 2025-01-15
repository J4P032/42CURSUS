/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:05:22 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/14 12:00:51 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_findstr(const char *s1, const char *s2, size_t l)
{
	size_t	i;
	size_t	j;
	size_t	pos;

	i = 0;
	j = 0;
	pos = 0;
	while ((s1[i] != '\0') && (i < l))
	{
		while ((s1[i] == s2[j]) && (s1[i] != '\0') && (i < l))
		{
			if (s2[j] != '\0')
			{
				i++;
				j++;
			}
			pos = i;
		}
		if (s2[j] == '\0')
			return (pos - j);
		j = 0;
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	found_position;
	size_t	i;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	found_position = ft_findstr(big, little, len);
	if (found_position == 0)
		return (0);
	else
		return ((char *)&big[found_position]);
}
