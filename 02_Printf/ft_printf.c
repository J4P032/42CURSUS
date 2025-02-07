/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:33:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/07 17:00:56 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_write(char const *str, va_list param)
{
	char	*num;
	
	num = NULL;
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

/*original printf returns number of chars printed to verify error*/
int	ft_printf(char const *str, ...)
{
	
	if (check_printf_flag_error(str)) //si da 1 es error. Si es 0 puede continuar
		return (1);
	va_list	params;
	va_start(params, str);

	ft_write(str, params);
	
	va_end(params);
	
	return (0);
}

#include <stdio.h>
int main ()
{
	ft_printf("hola % %zu", 5, 8);
	//printf("hola %zk");
	return (0);
}
