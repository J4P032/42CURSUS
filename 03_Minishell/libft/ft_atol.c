/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:42:58 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/18 19:10:43 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	check_overflow(int minus, long long result, int digit, int *error)
{
	if (minus == 1)
	{
		if (result > (LLONG_MAX - digit) / 10)
			*error = 1;
	}
	else
	{
		if (result > LLONG_MAX / 10)
			*error = 1;
		else if (result == LLONG_MAX / 10 && digit > 8)
			*error = 1;
	}
}

char	*clean_ceros(char *number, int *error)
{
	int	negative;

	negative = 0;
	if (!number || !*number)
		return (NULL);
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
long long	ft_atol(char *nptr, int *error)
{
	long long int	result;
	int				minus;

	minus = 1;
	result = 0;
	nptr = clean_ceros(nptr, error);
	if (!nptr)
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
