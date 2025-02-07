/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:08:01 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/07 11:25:44 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_flag_error(char c)
{
	write(2, "%", 1);
	write(2,&c, 1);
	write(2, " is NOT a valid flag for ft_printf", 34);
}	

int	check_printf_flag_error(char const *str)
{
	size_t	i;
	size_t	len;
	char	*flag;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		while(str[i] && str[i] != '%')
			i++;
		if (i == len)
			return (0);
		flag = ft_strchr(FLAGS, str[++i]);
		if (!flag)
		{
			write_flag_error(str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
