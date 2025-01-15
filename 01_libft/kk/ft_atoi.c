/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:05:07 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/14 19:06:05 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* isspace(3) consider spaces (space, \t \n \v \r \f */
/* minus (-) odd = +, even = - */
/* overflow or underflow correct. No need of long int */

/* 1=nums | 2=- | 3=isspaces | 4=+ */
int	ft_fc(char l)
{
	if (l < 9)
		return (0);
	if ((l == 32) || ((l < 14) && (l > 8)))
		return (3);
	if ((l > 13) && (l < 32))
		return (0);
	if ((l > 32) && (l < 43))
		return (0);
	if (l == 44)
		return (0);
	if ((l > 45) && (l < 48))
		return (0);
	if ((l >= '0') && (l <= '9'))
		return (1);
	else
		return (0);
}

int	ft_convert(const char *number)
{
	int	i;
	int	convert;
	int	solution;

	i = 0;
	convert = 0;
	if (!number)
		return (0);
	while (number)
	{
		solution = ft_fc(number[i]);
		if (solution == 1)
			convert = (convert * 10) + (number[i] - '0');
		else
			return (convert);
		i++;
	}
	return (convert);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	minus;
	int	i;

	result = 0;
	minus = 0;
	i = 0;
	if (!nptr)
		return (0);
	while (nptr[i] != '\0' && ft_fc(nptr[i]) == 3)
		i++;
	if (nptr[i] != '\0' && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			minus = 1;
		i++;
	}	
	if (minus == 1)
		result = -1 * ft_convert(&nptr[i]);
	else
		result = ft_convert(&nptr[i]);
	return (result);
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char kk[100] = "-2147483647 -1";
//	char kk[100] = "";
//	char kk[100] = "  -x32434";
//	char *kk = NULL;
	printf("array:%d", ft_atoi(kk));
	printf("\n atoi:%d", atoi(kk));
	return 0;

}
