/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_other_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:41:18 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/27 19:59:04 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

/*mimic printf with TWOFLAGS defined in .h*/
void	print_two_flags(const char **str, int *num_chars)
{
	write(1, "%", 1);
	write(1, *str, 1);
	*num_chars += 2;
}

/*NEGFLAGS is very arbitrary mimic some of the behaviours of it*/
/*if the NEGFLAG letter is only one and final of string it returns -1*/
/* if *(*str) == '\0' when % is final of string */
/* %C ignores after the %C */
void	other_flags(const char **str, int *num_chars)
{
	if ((**str) && (ft_strchr(NEGFLAGS, *(*str))))
	{
		if (*(*str + 1) == '\0')
			*num_chars = -1;
		else
		{
			write (1, "%", 1);
			*num_chars += 1;
		}
	}
	else if (*(*str) == '\0')
	{
		*num_chars = -1;
		(*str)--;
	}
	else if (*(*str) == 'C')
	{
		*num_chars = -1;
		while (**str)
			(*str)++;
	}
	else if (ft_strchr(TWOFLAGS, *(*str)))
		print_two_flags(str, num_chars);
}
