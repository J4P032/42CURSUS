/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:56:12 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/11 15:53:23 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_flag_dic(char const **str, va_list parm, int *numc, int opt)
{
	char	*num;
	char	*aux;

	++(*str);
	if (opt == 1)
	{
		num = ft_itoa(va_arg(parm, int));
		aux = num;
		while (aux && *aux)
		{
			write(1, aux++, 1);
			(*numc)++;
		}
		free (num);
		num = NULL;
	}
	else
	{
		write(1, (char []){va_arg(parm, int)}, 1);
		(*numc)++;
		str++;
	}
}

void	ft_print_flag_u(char const **str, va_list parm, int *num_chars)
{
	char	*num;
	char	*aux;

	++(*str);
	num = ft_utoa(va_arg(parm, unsigned int));
	aux = num;
	while (aux && *aux)
	{
		write(1, aux++, 1);
		(*num_chars)++;
	}
	free (num);
	num = NULL;
}


void	ft_print_flag_p(char const **str, va_list params, int *num_chars)
{
	unsigned long	aux;
	char			*base;

	base = HEX_LOW;
	aux = (unsigned long) va_arg(params, void *);
	if (aux)
	{
		write(1, "0x", 2);
		*num_chars += 2;
	}
	else
	{
		++(*str);
		write(1, "(nil)", 5);
		*num_chars += 5;
		return ;
	}
	++(*str);
	ft_putnbr_base(&aux, base, num_chars);
}

void	ft_print_flag_x(char const **str, va_list param, int *num_c, char c)
{
	unsigned int	aux;
	char			*base;

	if (c == 'x')
		base = HEX_LOW;
	else
		base = HEX_UP;
	aux = va_arg(param, unsigned int);
	++(*str);
	ft_putnbr_base32(&aux, base, num_c);
}

void	ft_print_flag_s(char const **str, va_list param, int *num_chars)
{
	char	*aux;
	size_t	length;

	aux = va_arg(param, char *);
	length = ft_strlen(aux);
	++(*str);
	write(1, aux, length);
	*num_chars += length;
}
