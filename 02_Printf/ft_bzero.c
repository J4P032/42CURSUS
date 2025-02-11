/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:47:13 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/11 16:03:31 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*set to '\0' all n memory places starting by address pointed by s*/
void	ft_bzero(void *s, size_t n)
{
	size_t			index;
	unsigned char	*ptr;

	index = 0;
	if (!s)
		return ;
	ptr = (unsigned char *)s;
	while (index < n)
	{
		ptr[index] = '\0';
		index++;
	}
}
