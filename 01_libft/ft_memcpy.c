/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:32:31 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/26 18:19:07 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*copy n bytes from src memory to mem area dest. They must not overlap*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*aux_dest;
	unsigned char	*aux_src;

	if ((n == 0) || (dest == src))
		return (dest);
	aux_dest = (unsigned char *)dest;
	aux_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*(aux_dest + i) = *(aux_src + i);
		i++;
	}
	return (dest);
}
