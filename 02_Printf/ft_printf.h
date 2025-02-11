/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:24:00 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/11 20:55:47 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef FLAGS
#  define FLAGS "cspdiuxX%"
# endif

# ifndef NEGFLAGS
#  define NEGFLAGS "ChIjlLnqStzZ012345679#*-+'."
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
int		checkflag(const char *str);
void	other_flags(const char **str, int *num_chars);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
void	ft_print_flag_dic(char const **str, va_list prm, int *numc, int opt);
void	ft_print_flag_p(char const **str, va_list params, int *num_chars);
void	ft_print_flag_x(char const **str, va_list param, int *num_c, char c);
void	ft_putnbr_base(unsigned long *nbr, char *base, int *num_chars);
void	ft_putnbr_base32(unsigned int *nbr, char *base, int *num_chars);
char	*ft_utoa(unsigned n);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
void	ft_print_flag_u(char const **str, va_list parm, int *num_chars);
void	ft_print_flag_s(char const **str, va_list param, int *num_chars);

#endif
