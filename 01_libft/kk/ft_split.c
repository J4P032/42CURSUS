/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: japo32 <jrollon-@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:41:14 by japo32            #+#    #+#             */
/*   Updated: 2024/12/20 14:03:19 by japo32           ###   ########.fr       */
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
/*Modify same str to just put the \0 when the characters starts to repeat.*/
char	*ft_separators(char *str)
{
	int		i;
	int		j;
	int		k;
	
	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (j < i)
		{	
			if (str[i] == str[j])
				break ;
			j++;
		}
		if (i == j)
		{
			str[k] = str[i];
			k++;
		}
		i++;
	}
	str[k] = '\0';
	return (str);
}

/*
char	*ft_separators(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*aux;
	int		size;
	
	i = 0;
	k = 0;
	size = ft_strlen(str);
	aux = (char *)malloc(size * sizeof(char));
	if (!aux)
		return (NULL);
	while (str[i] != '\0')
	{
		j = 0;
		while (j < k)
		{	
			if (str[i] == aux[j])
				break ;
			j++;
		}
		if (j == k)
		{
			aux[k] = str[i];
			k++;
		}
		i++;
	}
	aux[k] = '\0';
	return (aux);
}*/
/*
char	**ft_split(char *str, char *charset)
{
	


}*/
#include <stdio.h>

int	main(int argc, char **argv)
{
	//char	**solution;

	if (argc != 3)
		return (0);
	//solution = ft_split(argv[1], argv[2])
	printf("\n%s", ft_separators(argv[2]));

	return (0);
}

