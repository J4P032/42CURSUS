/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 08:33:05 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/19 09:56:33 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*if size src + size dest > size given only will copy the chars that fit and
will set a \0 in last one. If size is less or equal to the size of dest, then
will return the necesary space needed to proceed with that secure.
*/
static size_t	ft_size(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	size_dest;
	size_t	size_src;

	i = 0;
	size_dest = ft_size(dst);
	size_src = ft_size(src);
	if (size <= size_dest)
		return (size + size_src);
	while (src[i] != '\0' && (size_dest + i < size - 1))
	{
		dst[size_dest + i] = src[i];
		i++;
	}
	dst[size_dest + i] = '\0';
	return (size_dest + size_src);
}
