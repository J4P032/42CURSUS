/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:48:15 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/19 09:55:32 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*copy data from src to dest through n bytes but garanties good copy of all*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*aux_dest;
	unsigned char	*aux_src;

	if (!dest && !src)
		return (0);
	aux_dest = (unsigned char *)dest;
	aux_src = (unsigned char *)src;
	i = 0;
	if (dest > src)
	{
		while (n--)
			aux_dest[n] = aux_src[n];
	}
	else
	{
		while (i < n)
		{
			*(aux_dest + i) = *(aux_src + i);
			i++;
		}
	}
	return (dest);
}
