/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:07:48 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/24 18:40:41 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*returns in string format the int number given*/
/*NULL if not MALLOC*/

static int	ft_num_digits(long num, int *div)
{
	int	digits;

	if (num == 0)
		return (1);
	digits = 10;
	while (num / *div == 0)
	{
		digits--;
		*div /= 10;
	}
	return (digits);
}

static char	*compose_number(char *s, long number, int div, size_t digits)
{
	size_t	i;

	i = 0;
	while (i < digits)
	{
		s[i] = (number / div) + '0';
		number %= div;
		div /= 10;
		i++;
	}
	return (s);
}

/* divisor is max possible for MAX_INT will be reducing in ft_numb_digits*/
/*if negative = 1 add one byte to calloc and start index 1 in char *number*/

char	*ft_itoa(int n)
{
	long	aux;
	size_t	negative;
	int		divisor;
	char	*number;
	size_t	num_digits;

	aux = n;
	divisor = 1000000000;
	negative = 0;
	if (n < 0)
	{
		aux = -aux;
		negative = 1;
	}
	num_digits = ft_num_digits(aux, &divisor);
	number = (char *)ft_calloc(num_digits + negative + 1, sizeof(char));
	if (!number)
		return (NULL);
	if (negative)
		number[0] = '-';
	compose_number(&number[negative], aux, divisor, num_digits);
	return (number);
}
