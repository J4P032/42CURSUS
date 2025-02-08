/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:33:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/08 13:33:46 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h> ///


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
	int	num_flags;
	
	num_flags = check_printf_flag_error(str);
	printf("\n\nel num de flags es: %d", num_flags); //
	if (num_flags == -1) //si da -1 es error. si no da num de % validos
		return (1);
	va_list	params;
	va_start(params, str);
	ft_write(str, params);
	
	va_end(params);
	
	return (0);
}


int main ()
{
	ft_printf("hola %d %p %i atata", 5, 8);
	//printf("hola %zk");
	return (0);
}
