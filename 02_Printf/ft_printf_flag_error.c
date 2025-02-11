/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:08:01 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/11 17:34:27 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*Check if flags are correct. I included %zu for size_t ones*/
/*will check next char to see if belong to valid ones*/
/*if valid will return 1, if not will return 0*/
int	checkflag(const char *str)
{
	if (!*(str + 1))
		return(0);
	else if ((str + 1) && (str + 2) && *(str + 1) == 'z' && *(str + 2) == 'u')
		return (1);
	else if ((str + 1) && (str + 2) && *(str + 1) == 'z' && *(str + 2) != 'u')
		return (0);
	else if ((str + 1) && !ft_strchr(FLAGS, *(str + 1)))
		return (0);
	else if ((str + 1) && ft_strchr(FLAGS, *(str + 1)))
		return (1);
	return (0);
}
