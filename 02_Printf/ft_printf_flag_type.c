/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:56:12 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/12 17:45:10 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*option 1: int numbers*/
/*option different 1: chars*/
/*((*(*str - 1) == ' ') && (aux[0] != '-')) mimic when letter spaced from % */
void	ft_print_flag_dic(char const **str, va_list parm, int *numc, int opt)
{
	char	*num;
	char	*aux;

	if (opt == 1)
	{
		num = ft_itoa(va_arg(parm, int));
		aux = num;
		if ((*(*str - 1) == ' ') && (aux[0] != '-'))
		{
			write(1, " ", 1);
			(*numc)++;
		}
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
	}
}

void	ft_print_flag_u(va_list parm, int *num_chars)
{
	char	*num;
	char	*aux;

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

/* (*(*str - 1) == ' ') mimic when letter spaced from % */
void	ft_print_flag_p(char const **str, va_list params, int *num_chars)
{
	unsigned long	aux;
	char			*base;

	base = HEX_LOW;
	aux = (unsigned long) va_arg(params, void *);
	if (aux)
	{
		if (*(*str - 1) == ' ')
		{
			write(1, " ", 1);
			(*num_chars)++;
		}
		write(1, "0x", 2);
		*num_chars += 2;
	}
	else
	{
		write(1, "(nil)", 5);
		(*num_chars) += 5;
		return ;
	}
	ft_putnbr_base(&aux, base, num_chars);
}

void	ft_print_flag_x(va_list param, int *num_c, char c)
{
	unsigned int	aux;
	char			*base;

	if (c == 'x')
		base = HEX_LOW;
	else
		base = HEX_UP;
	aux = va_arg(param, unsigned int);
	ft_putnbr_base32(&aux, base, num_c);
}

void	ft_print_flag_s(va_list param, int *num_chars)
{
	char	*aux;
	size_t	length;

	aux = va_arg(param, char *);
	if (aux)
	{
		length = ft_strlen(aux);
		write(1, aux, length);
		*num_chars += length;
	}
	else
	{
		write(1, "(null)", 6);
		*num_chars += 6;
	}
}
