/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:53:34 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/17 17:14:04 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"

/*allocates memory for array of nmemb elements of size bytes*/
/*returns a pointer to that memory. Memory is set to zeros*/
/*if nmemb x size is > INT_MAX returns NULL*/
/*if nmemb or size == 0 unknown but can be valid pointer without memory alloc*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_bytes;
	unsigned char	*ptr;

	total_bytes = nmemb * size;
	if (nmemb == 0 || size == 0)
	{
		ptr = (unsigned char *)malloc(0);
		return (ptr);
	}
	if (total_bytes < nmemb || total_bytes < size || total_bytes > INT_MAX)
		return (NULL);
	ptr = (unsigned char *)malloc(total_bytes);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_bytes);
	return (ptr);
}
