/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:42:58 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/09 19:15:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

/*checks if the 'c' is a number (0-9)*/
int	ft_isdigit(int c)
{
	if ((c < '0') || (c > '9'))
		return (0);
	else
		return (1);
}

void	check_overflow(int minus, long result, int digit, int *error)
{
	if (minus == 1 && result > (LONG_MAX - digit) / 10)
		*error = 1;
	if (minus == -1 && result > (-(LONG_MIN + digit) / 10))
		*error = 1;
}

char	*clean_ceros(char *number, int *error)
{
	int	negative;

	negative = 0;
	if (!number || !*number)
		return (printf("Error: Empty Argument\n"), NULL);
	if ('-' == *number)
	{
		negative = 1;
		number++;
	}
	if ('+' == *number)
		number++;
	if (!*number)
		*error = 1;
	while ('0' == *number && *(number + 1))
		number++;
	if (ft_strlen(number) > 19)
		*error = 1;
	if (*number && negative)
	{
		*(number - 1) = '-';
		number--;
	}
	return (number);
}

/*first clean zeros as a valid number could be longer than 19chars with all 0*/
/*if any char different than 0-9 is found then error..*/
long int	ft_atol(char *nptr, int *error)
{
	long int	result;
	int			minus;

	minus = 1;
	result = 0;
	if (!(nptr = clean_ceros(nptr, error)))
		*error = 1;
	if (nptr && *nptr && (*nptr == '-' || *nptr == '+'))
	{
		if (*nptr == '-')
			minus = -1;
		nptr++;
	}
	while (nptr && *nptr && *error == 0)
	{
		if (!ft_isdigit(*nptr))
		{
			*error = 1;
			return (0);
		}
		check_overflow(minus, result, *nptr - '0', error);
		result = (result * 10) + (*nptr++ - '0');
	}
	return (minus * result);
}
