/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:24:00 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/07 17:12:07 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef FLAGS
#  define FLAGS "cspdiuxX%"
# endif

# include "./libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(char const *str, ...);
int	check_printf_flag_error(char const *str);

#endif
