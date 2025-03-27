/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:24:00 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/27 19:52:10 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef FLAGS
#  define FLAGS "cspdiuxX%"
# endif

# ifndef NEGFLAGS
#  define NEGFLAGS "hIjlLqtzZ012345679#*-+'."
# endif

# ifndef TWOFLAGS
#  define TWOFLAGS "DHJkKMNOPQrRTUvVwWyY"
# endif

# ifndef HEX_LOW
#  define HEX_LOW "0123456789abcdef"
# endif

# ifndef HEX_UP
#  define HEX_UP "0123456789ABCDEF"
# endif

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(char const *str, ...);
void	other_flags(const char **str, int *num_chars);
void	ft_print_flag_dic(char const **str, va_list prm, int *numc, int opt);
void	ft_print_flag_p(char const **str, va_list params, int *num_chars);
void	ft_print_flag_x(va_list param, int *num_c, char c);
void	ft_print_flag_u(va_list parm, int *num_chars);
void	ft_print_flag_s(va_list param, int *num_chars);
void	print_two_flags(const char **str, int *num_chars);

#endif
