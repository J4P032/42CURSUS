/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:56:12 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/08 14:51:25 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_print_flag_di(char const **str, va_list params, size_t *num_chars)
{
	char	*num;
	
	++(*str);
	num = ft_itoa(va_arg(params, int));
	while (num && *num)
	{
		write(1, num++, 1);
		(*num_chars)++;
	}
}
