/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:11:39 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/20 20:31:18 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_give_divisor(int nb)
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

void	ft_putnbr_fd(int n, int fd)
{
	int			division;
	int			ext_num;
	long int	aux;

	aux = n;
	division = ft_give_divisor(n);
	if (aux < 0)
	{
		aux = -1 * aux;
		write(fd, "-", 1);
	}
	while ((aux % division != 0) || (division > 1))
	{
		ext_num = (aux / division) + '0';
		write(fd, &ext_num, 1);
		aux = aux % division;
		division = division / 10;
	}
	ext_num = aux + '0';
	write(fd, &ext_num, 1);
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
