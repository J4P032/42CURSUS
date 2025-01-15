/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:29:41 by jrollon-          #+#    #+#             */
/*   Updated: 2024/12/06 18:16:02 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	int		src_size;
	char	*cpy;
	int		i;

	i = 0;
	src_size = ft_strlen(src);
	cpy = (char *)malloc((src_size + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	while (i < src_size)
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
/*
#include <unistd.h>
#include <stdio.h>
int	main(int argc, char **argv)
{
	char *cpy;

	if (argc != 2)
	{
		write(2, "One String argument needed!\n", 28);
		return (0);
	}
	cpy = ft_strdup(argv[1]);
	printf("La copia del String es: %s\n", cpy);
	free(cpy);
	return (0);
}*/
