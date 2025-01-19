/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:05:22 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/19 09:57:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_findstr(const char *s1, const char *s2, size_t l)
{
	size_t	i;
	size_t	j;
	size_t	pos;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	pos = 0;
	while ((s1[i]) && (i < l))
	{
		k = i;
		while ((s1[k] == s2[j]) && (s1[k]) && (k < l))
		{
			if (s2[j])
				j++;
			pos = ++k;
		}
		if (s2[j] == '\0')
			return (pos - j);
		j = 0;
		i++;
	}
	return (-1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		found_position;

	if (little[0] == '\0')
		return ((char *)big);
	found_position = ft_findstr(big, little, len);
	if (found_position == -1)
		return (0);
	else
		return ((char *)&big[found_position]);
}
