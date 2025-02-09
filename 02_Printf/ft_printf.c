/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:33:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/09 14:58:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h> ///

/* (char[]){va_arg(param, int)} I trick forming an array of ony a char with..*/
/*..va_arg(param,int) so it will have the address of that string to print*/
void	ft_write(char const *str, va_list param, size_t *num_chars)
{
	while (str && *str)
	{
		if (*str == '%')
		{
			if ((*++str == 'd') || (*str == 'i'))
				ft_print_flag_di(&str, param, num_chars);
			else if (*str == 'c')
			{
				write(1, (char []){va_arg(param, int)}, 1);
				(*num_chars)++;
				str++;
			}
			else if (*str == 'p')
				ft_print_flag_p(&str, param, num_chars);
		}
		if (str && *str)
		{
			write(1, str++, 1);
			(*num_chars)++;
		}
	}
}

/*original printf returns number of chars printed to verify error*/
int	ft_printf(char const *str, ...)
{
	int		num_flags;
	size_t	num_chars;

	num_chars = 0;
	num_flags = check_printf_flag_error(str);
	if (num_flags == -1) //si da -1 es error. si no da num de % validos
		return (1);
	va_list	params;
	va_start(params, str);
	ft_write(str, params, &num_chars);
	
	
	
	va_end(params);
	printf("\nEl num de chars es: %zu\n", num_chars);
	
	return (num_chars);
}


int main ()
{
	void *puntero;
	puntero = (void *)malloc(34);
	
	printf("puntero printf: %p", puntero);
	fflush(stdout);
	ft_printf("\npuntero: %p", puntero);
	//ft_printf("adios%%");
	//printf("hola %zk");
	return (0);
}
