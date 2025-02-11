/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_other_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:41:18 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/11 20:43:09 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>///

void	other_flags(const char **str, int *num_chars)
{
	if (ft_strchr(NEGFLAGS, *(*str + 1)))
	{
		*num_chars = -1;
		*str += 2;
	}
	else if (*(*str + 1) == '\0')
	{
		*num_chars = -1;
		(*str)++;
	}

}
