/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:24:13 by jrollon-          #+#    #+#             */
/*   Updated: 2024/11/18 12:24:15 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char	*dest, char	*src)
{
	int	i;
	int	size_dest;

	i = 0;
	size_dest = 0;
	while (dest[i] != '\0')
	{
		i++;
		size_dest = i;
	}
	i = 0;
	while (src[i] != '\0')
	{
		dest[size_dest] = src[i];
		i++;
		size_dest++;
	}
	dest[size_dest] = '\0';
	return (dest);
}
/*
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	i = 0;
	char	s1[] = "EFGH";
	char	s2[10] = "ABCD";
	
	ft_strcat(s2, s1);
	int	size = sizeof(s2);
	printf("Concatenados: %s\n", s2);
	while ( i <= size)
	{
		if (s2[i] == '\0')
			write(1, "#", 1);
		else
			write(1, &s2[i], 1);
	i++;
	}

	return (0);
}*/
