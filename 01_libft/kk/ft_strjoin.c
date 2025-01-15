/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: japo32 <jrollon-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:58:22 by japo32            #+#    #+#             */
/*   Updated: 2024/12/09 14:51:26 by japo32           ###   ########.fr       */
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

int	ft_strslen(int size, char **strs, char *sep)
{
	int	size_total;
	int	size_sep;
	int	i;

	i = 0;
	size_total = 0;
	size_sep = ft_strlen(sep);
	while (i < size)
	{
		size_total = size_total + ft_strlen(strs[i]);
		i++;
	}
	size_total = size_total + (size_sep * (size - 1));
	return (size_total);
}

void	ft_compose_str(int size, char *solution, char **strs, char *sep)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < size)
	{
		j = 0;
		while (strs[i][j] != '\0')
			solution[k++] = strs[i][j++];
		j = 0;
		if ((i + 1) != size)
		{
			while (sep[j] != '\0')
				solution[k++] = sep[j++];
		}
		i++;
	}
	solution[k] = '\0';
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*solution;
	int		size_str;

	if (size == 0)
	{
		solution = (char *)malloc(sizeof(char));
		if (!solution)
			return (NULL);
		solution[0] = '\0';
		return (solution);
	}
	size_str = ft_strslen(size, strs, sep);
	solution = (char *)malloc((size_str + 1) * sizeof(char));
	if (!solution)
		return (NULL);
	ft_compose_str(size, solution, strs, sep);
	return (solution);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*strs[] = {"patata", "flipa", "a", "pepe", "viento", "42"};
	char	spaces[] = ".-.";
	int		size = 6;
	char	*solution;	

	solution = ft_strjoin(size, strs, spaces);
	printf("La cadena es: \n%s", solution);
	free(solution);
	return (0);
}*/
