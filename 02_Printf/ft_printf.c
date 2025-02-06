/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:33:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/06 21:10:06 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>


void	ft_write(char const *str, va_list param)
{
	char	*num;
	while (str && *str)
	{
		if (*str == '%')
		{
			if (*++str == 'd')
			{
				str++;
				num = ft_itoa(va_arg(param, int));
				while (num && *num)
					write(1, num++, 1);
			}
		}	
		if (str && *str)
			write(1, str++, 1);
	}
}

int	ft_printf(char const *str, ...)
{
	va_list	params;
	va_start(params, str);

	ft_write(str, params);
	
	va_end(params);
	
	return (0);
}

#include <stdio.h>
int main ()
{
	ft_printf("el numero es %d", 2);
	//printf("hola %d %d", 4);
	return (0);
}
