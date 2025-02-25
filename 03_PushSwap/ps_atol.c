/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:31:45 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/21 16:52:14 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
/*if any char different than 0-9 is found then error.*/
long int	ps_atol(char *nptr, int *error)
{
	long int	result;
	int			minus;
	
	minus = 1;
	result = 0;
	nptr = clean_ceros(nptr, error);
	if (*nptr && (*nptr == '-' || *nptr == '+'))
	{
		if (*nptr == '-')
			minus = -1;
		nptr++;
	}
	while (*nptr && *error == 0)
	{
		if (!ft_isdigit(*nptr))
		{
			*error = 1;
			return (0);
		}
		result = (result * 10) + (*nptr++ - '0');
	}
	if (minus * result > 2147483647 || minus * result < -2147483648)
		*error = 1;
	return (minus * result);
}


/* 
#include <stdio.h>
int main()
{
	char a[] = "21474836493de34";
	long int b = ps_atol(a);
	printf ("el num es: %ld", b);
	return (0);
	
	
	
} */

