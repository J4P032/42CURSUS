/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:36:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/16 18:05:36 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
size_t	ft_size(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_findstr(const char *s1, const char *s2, size_t l);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *nptr);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);

#endif
