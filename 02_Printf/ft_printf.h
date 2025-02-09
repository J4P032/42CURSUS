/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:24:00 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/09 14:48:47 by jrollon-         ###   ########.fr       */
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

int		ft_printf(char const *str, ...);
int		check_printf_flag_error(char const *str);
void	ft_print_flag_di(char const **str, va_list params, size_t *num_chars);
void 	ft_print_flag_p(char const **str, va_list params, size_t *num_chars);
void	ft_putnbr_base(unsigned long *nbr, char *base);

#endif
