/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:31:45 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/20 14:45:59 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*converts from string to number long int*/
long int	ps_atol(const char *nptr)
{
	long int	result;
	int			minus;
	size_t		i;

	minus = 1;
	i = 0;
	result = 0;
	while (nptr[i] != 0 && ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32))
		i++;
	if (nptr[i] != '\0' && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			minus = -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (minus * result);
}

#include <stdio.h>
int main()
{
	char a[] = "21474836493de34";
	long int b = ps_atol(a);
	printf ("el num es: %ld", b);
	return (0);
	
	
	
}
