/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:43:12 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/20 09:09:15 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*search for first byte with char c in first n bytes of s*/
/*if not found -> NULL*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_aux;
	unsigned char	c_aux;
	size_t			i;

	s_aux = (unsigned char *)s;
	c_aux = (char)c;
	i = 0;
	while (i < n)
	{
		if (s_aux[i] == c_aux)
			return (&s_aux[i]);
		i++;
	}
	return (NULL);
}
