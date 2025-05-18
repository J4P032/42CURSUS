/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:33:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/27 19:55:07 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*option 1: writes normal string except if it comes in %*/
/*option 0: when find %%*/
void	ft_write_normal(char const **str, int *num_chars, int option)
{
	if (*str && **str && option == 1)
	{
		if (**str != '%')
		{
			write(1, (*str)++, 1);
			if (*num_chars >= 0)
				(*num_chars)++;
		}
	}
	else if (*str && **str)
	{
		write(1, "%", 1);
		(*num_chars)++;
	}
}

void	ft_write(char const *str, va_list param, int *num_chars)
{
	while (str && *str)
	{
		if (*str == '%')
		{
			while (*(str + 1) == ' ')
				str++;
			if ((*++str == 'd') || (*str == 'i'))
				ft_print_flag_dic(&str, param, num_chars, 1);
			else if (*str == 'c')
				ft_print_flag_dic(&str, param, num_chars, 0);
			else if (*str == 'p')
				ft_print_flag_p(&str, param, num_chars);
			else if ((*str == 'x') || (*str == 'X'))
				ft_print_flag_x(param, num_chars, *str);
			else if (*str == 'u')
				ft_print_flag_u(param, num_chars);
			else if (*str == 's')
				ft_print_flag_s(param, num_chars);
			else if (*str == '%')
				ft_write_normal(&str, num_chars, 0);
			other_flags(&str, num_chars);
			str++;
		}
		ft_write_normal(&str, num_chars, 1);
	}
}

/*original printf returns number of chars printed to verify error*/
int	ft_printf(char const *str, ...)
{
	int		num_chars;
	va_list	params;

	num_chars = 0;
	va_start(params, str);
	ft_write(str, params, &num_chars);
	va_end(params);
	return (num_chars);
}
