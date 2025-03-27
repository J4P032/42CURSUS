/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:53:34 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/25 13:52:04 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*allocates memory for array of nmemb elements of size bytes*/
/*returns a pointer to that memory. Memory is set to zeros*/
/*if nmemb x size is > SIZE_MAX (~(size_t)0) returns NULL*/
/*if nmemb or size == 0 unknown but can be valid pointer without memory alloc*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_bytes;
	unsigned char	*ptr;

	if (nmemb == 0 || size == 0)
		return (NULL);
	if (nmemb > (size_t)-1 / size)
		return (NULL);
	total_bytes = nmemb * size;
	ptr = (unsigned char *)malloc(total_bytes);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_bytes);
	return (ptr);
}
