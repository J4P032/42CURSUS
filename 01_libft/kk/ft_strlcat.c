/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:08:29 by jrollon-          #+#    #+#             */
/*   Updated: 2024/11/19 09:10:48 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*if size src + size dest > size given only will copy the chars that fit and 
will set a \0 in last one. If size is less or equal to the size of dest, then
will return the necesary space needed to proceed with that secure.
*/
int	ft_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	size_dest;
	unsigned int	size_src;

	i = 0;
	size_dest = ft_size(dest);
	size_src = ft_size(src);
	if (size <= size_dest)
		return (size + size_src);
	while (src[i] != '\0' && (size_dest + i < size - 1))
	{
		dest[size_dest + i] = src[i];
		i++;
	}
	dest[size_dest + i] = '\0';
	return (size_dest + size_src);
}
/*
#include <unistd.h>
#include <stdio.h>

int	main()
{
	int			i;
	char		s1[] = " World";
	char		s2[11] = "Hello";
	unsigned	int	size = 9;
	i = 0;

	unsigned int	result = ft_strlcat(s2, s1, size);
	while (i < 15)
	{
		if (s2[i] == '\0')
			write(1, "#", 1);
		write(1, &s2[i], 1);
		i++;
	}
	printf("\ntamaño total: %u", result);
	return (0);
}*/
