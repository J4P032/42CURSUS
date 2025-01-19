/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:15:04 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/19 09:55:46 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*fills 1st n bytes of memory pointed by s with constant byte c*/
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*ptr;

	index = 0;
	ptr = (unsigned char *)s;
	while (index < n)
	{
		ptr[index] = (unsigned char)c;
		index++;
	}
	return (s);
}
