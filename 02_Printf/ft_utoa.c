/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:36:45 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/11 10:07:34 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*returns in string format the int number given*/
/*NULL if not MALLOC*/

static int	ft_num_digits(unsigned int num, int *div)
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

/* divisor is max possible for UNSIGNED will be reducing in ft_numb_digits*/
char	*ft_utoa(unsigned n)
{
	unsigned int	aux;
	int				divisor;
	char			*number;
	size_t			num_digits;

	aux = n;
	divisor = 1000000000;
	num_digits = ft_num_digits(aux, &divisor);
	number = (char *)ft_calloc(num_digits + 1, sizeof(char));
	if (!number)
		return (NULL);
	compose_number(number, aux, divisor, num_digits);
	return (number);
}
