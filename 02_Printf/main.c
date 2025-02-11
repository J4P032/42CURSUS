/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:35:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/11 21:46:48 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main (void)
{
	int				num_chars;
	int				num_printf;
	char			c = 'j';
	void 			*punt_null = NULL;
	void 			*puntero = (void *)malloc(34);
	unsigned int 	num = 4294967295;
	char			str[] = "hola mundo!";

	num_printf = printf("%h hola");
	printf("\n");
	num_chars = ft_printf("lechuga %. lechuga ");
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	printf("char: %c", c);
	printf("\n");
	num_chars = ft_printf("char: %c", c);
	printf("\nNumChars: %d", num_chars);

	printf("\n\n");

	free (puntero);
	return (0);
}
