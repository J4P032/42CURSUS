/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:17:41 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/19 09:56:21 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Joins both s1 first and s2 in a new string with memory allocation*/
/*if Mem alloc is not success then return NULL*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*dest;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	dest = (char *)ft_calloc(((s1_len + s2_len) + 1), sizeof(char));
	if (!dest)
		return (NULL);
	while (i < (s1_len + s2_len))
	{
		if (i < s1_len)
			dest[i] = s1[i];
		if ((i + s1_len) < (s1_len + s2_len))
			dest[i + s1_len] = s2[i];
		i++;
	}
	return (dest);
}
