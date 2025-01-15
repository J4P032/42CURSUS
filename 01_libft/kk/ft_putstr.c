/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:07:46 by jrollon-          #+#    #+#             */
/*   Updated: 2024/11/12 17:09:55 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

/*
#include <stdio.h>

int	main(void)
{
	char	phrase[12] = "Hola mundo!";
	printf("%s\n", phrase);
	
	ft_putstr(phrase);
	return (0);
}
*/
/*
Nota el while se puede hacer mas pro asi:
while (*str)
{
        write(1, str, 1);
        str++;
}
*/
