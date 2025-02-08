/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:08:01 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/08 13:30:37 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*option 0: just one char flag error. ex: %w is not a valid...*/
/*option 1: for print different than %zu, example: %zk is not a valid...*/
/*option 2: for just printing '%' in case of % at the end of the string*/
void	write_flag_error(char c, int option)
{
	write(2, "%", 1);
	if (option == 0)
		write(2, &c, 1);
	if (option == 1)
	{
		write(2, "z", 1);
		write(2, &c, 1);
	}
	write(2, " is NOT a valid flag for ft_printf", 34);
}	

/*Check if flags are correct. I included %zu for size_t ones*/
/*runs all chars up to '%' then compares next one */
/*if next one is inside group of FLAGS in define ft_printf.h -> ok*/
/*returns number of valid %. %% is not count but is not an error*/
int	check_printf_flag_error(char const *str)
{
	size_t	num_flags;

	num_flags = 0;
	while (*str)
	{
		while(*str && *str != '%')
			str++;
		if (*str == '%' && !*(str + 1))
			return(write_flag_error('%', 2), -1);
		if (!*str)
			return (num_flags);
		if (*(++str) == 'z' && *(str + 1) == 'u')
			num_flags++;
		else if (*str == 'z' && *(str + 1) != 'u')
			return(write_flag_error(*(str + 1), 1), -1);
		else if (!ft_strchr(FLAGS, *str))
			return(write_flag_error(*str, 0), -1);
		if ((*str != 'z') && (*str != '%'))
			num_flags++;
		str++;
	}
	return (num_flags);
}
