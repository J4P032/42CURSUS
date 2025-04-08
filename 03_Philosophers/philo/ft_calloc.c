/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:29:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/08 11:31:51 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_bzero(void *s, size_t n)
{
	size_t			index;
	unsigned char	*ptr;

	index = 0;
	ptr = (unsigned char *)s;
	while (index < n)
	{
		ptr[index] = '\0';
		index++;
	}
}

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
