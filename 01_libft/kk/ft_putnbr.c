/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:27:35 by jrollon-          #+#    #+#             */
/*   Updated: 2024/11/22 10:18:49 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_give_divisor(int nb)
{
	int	i;

	i = 1000000000;
	if (nb == 0)
	{
		return (1);
	}
	while ((nb / i) == 0)
		i = i / 10;
	return (i);
}

void	ft_putnbr(int nb)
{
	int			division;
	int			ext_num;
	long int	aux;

	aux = nb;
	division = ft_give_divisor(nb);
	if (aux < 0)
	{
		aux = -1 * aux;
		write(1, "-", 1);
	}
	while ((aux % division != 0) || (division > 1))
	{
		ext_num = (aux / division) + '0';
		write(1, &ext_num, 1);
		aux = aux % division;
		division = division / 10;
	}
	ext_num = aux + '0';
	write(1, &ext_num, 1);
}
/*
#include <limits.h>
#include <unistd.h>

int	main(void)
{
	ft_putnbr(-0);
	write(1, "\n", 1);
	ft_putnbr(0);
	write(1, "\n", 1);
	ft_putnbr(INT_MAX);
	write(1, "\n", 1);
	ft_putnbr(INT_MIN);
	write(1, "\n", 1);
	ft_putnbr(-123456789);
	write(1, "\n", 1);
	ft_putnbr(-10000);
	write(1, "\n", 1);
	ft_putnbr(-02);
	return (0);
}*/
