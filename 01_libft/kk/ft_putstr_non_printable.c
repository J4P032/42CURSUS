/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:18:04 by jrollon-          #+#    #+#             */
/*   Updated: 2024/11/15 11:02:54 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* (hex converter) +48 to convert from int num to char num.
+87 to convert from 10 = a(97) to 15(102)=f
*/
#include <unistd.h>

char	*ft_hex(char a, char *hex)
{
	int		aux;
	char	hex_num;
	char	hex_char;

	hex_char = '0';
	aux = (a % 16);
	hex_num = (a / 16) + 48;
	if (aux < 9)
		hex_char = aux + 48;
	else if ((aux >= 10) && (aux <= 16))
		hex_char = aux + 87;
	hex[0] = hex_num;
	hex[1] = hex_char;
	return (hex);
}

void	ft_putstr_non_printable(char *str)
{
	int		i;
	char	hex[2];

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < 32) || (str[i] == 127))
		{
			write(1, "\\", 1);
			write(1, ft_hex(str[i], hex), 2);
		}
		else
			write(1, &str[i], 1);
		i++;
	}
}
/*
int	main(void)
{
	char	phrase[] = "hola\n estas b\bien ?";
	//char phrase[] = "Del \x7F startTxt \x02 bell \a";
	ft_putstr_non_printable(phrase);
	return (0);
}*/
