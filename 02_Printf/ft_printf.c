/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:33:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/11 19:48:35 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_write_normal(char const **str, int *num_chars)
{
	if (*str && **str)
	{
		write(1, (*str)++, 1);
		if (*num_chars >= 0)
			(*num_chars)++;
	}
}


/* (char[]){va_arg(param, int)} I trick forming an array of ony a char with..*/
/*..va_arg(param,int) so it will have the address of that string to print*/
void	ft_write(char const *str, va_list param, int *num_chars)
{
	while (str && *str)
	{
		if ((*str == '%') && checkflag(str))
		{
			if ((*++str == 'd') || (*str == 'i'))
				ft_print_flag_dic(&str, param, num_chars, 1);
			else if (*str == 'c')
				ft_print_flag_dic(&str, param, num_chars, 0);
			else if (*str == 'p')
				ft_print_flag_p(&str, param, num_chars);
			else if ((*str == 'x') || (*str == 'X'))
				ft_print_flag_x(&str, param, num_chars, *str);
			else if (*str == 'u')
				ft_print_flag_u(&str, param, num_chars);
			else if (*str == 's')
				ft_print_flag_s(&str, param, num_chars);
		}
		else if((*str == '%') && !checkflag(str))
			other_flags(&str, num_chars);
		ft_write_normal(&str, num_chars);
	}
}

/*original printf returns number of chars printed to verify error*/
int	ft_printf(char const *str, ...)
{
	int	num_chars;

	num_chars = 0;
	va_list	params;
	va_start(params, str);
	ft_write(str, params, &num_chars);



	va_end(params);



	return (num_chars);
}
