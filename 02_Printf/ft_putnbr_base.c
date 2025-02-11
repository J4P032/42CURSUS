/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:25:30 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/11 18:30:59 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*returns if the base is not valid because '+' '-' or repeated char found*/
/*if not valid returns 0 , if valid returns the number of elements of the base*/
int	ft_base_check(char *chr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	while (chr[i] != '\0')
	{
		if ((chr[i] == '+') || (chr[i] == '-'))
			return (0);
		while (chr[j] != '\0')
		{
			if (chr[i] == chr[j])
				return (0);
			j++;
		}
		i++;
		j = i + 1;
	}
	if (i < 2)
		return (0);
	return (i);
}

void	ft_conversion(unsigned long *num, int *base, char *aux)
{
	size_t	i;

	i = 0;
	while (*num / *base != 0 && i < 65)
	{
		aux[i] = (*num % *base) + '0';
		*num /= *base;
		i++;
	}
	if (i < 65)
		aux[i] = (*num % *base) + '0';
}

void	ft_conversion32(unsigned int *num, int *base, char *aux)
{
	size_t	i;

	i = 0;
	while (*num / *base != 0 && i < 33)
	{
		aux[i] = (*num % *base) + '0';
		*num /= *base;
		i++;
	}
	if (i < 33)
		aux[i] = (*num % *base) + '0';
}

void	ft_putnbr_base(unsigned long *nbr, char *base, int *num_chars)
{
	int		base_type;
	int		i;
	size_t	index;
	char	*aux;

	i = 64;
	index = 0;
	aux = (char *)ft_calloc(64, sizeof(char));
	if (!aux)
		return ;
	base_type = ft_base_check(base);
	if (base_type != 0)
		ft_conversion(nbr, &base_type, aux);
	while (i >= 0)
	{
		if (aux[i] != '\0')
		{
			index = aux[i] - '0';
			write(1, &base[index], 1);
			*num_chars = *num_chars + 1;
		}
		i--;
	}
	free (aux);
	aux = NULL;
}
void	ft_putnbr_base32(unsigned int *nbr, char *base, int *num_chars)
{
	int		base_type;
	int		i;
	size_t	index;
	char	*aux;

	i = 32;
	index = 0;
	aux = (char *)ft_calloc(32, sizeof(char));
	if (!aux)
		return ;
	base_type = ft_base_check(base);
	if (base_type != 0)
		ft_conversion32(nbr, &base_type, aux);
	while (i >= 0)
	{
		if (aux[i] != '\0')
		{
			index = aux[i] - '0';
			write(1, &base[index], 1);
			*num_chars = *num_chars + 1;
		}
		i--;
	}
	free (aux);
	aux = NULL;
}
