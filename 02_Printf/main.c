/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:35:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/12 17:55:33 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main (void)
{
	char			c = 'j';
	char			str[] = "hola mundo!";
	void 			*puntero = (void *)malloc(34);
	void 			*punt_null = NULL;
	int				num_dec = 32;
	int				num_zero = 0;
	int				max_int = 2147483647;
	int				max_intplus = 2147483648;
	int				min_int = -2147483648;
	int				min_intplus = -2147483649;
	unsigned int 	max_unsigned = 4294967295U;
	unsigned int 	max_unsignedPlus = 4294967296U;

	int				num_chars;
	int				num_printf;

	/////////////////////////////////////////////
	///VALIDOS
	////////////////////////////////////////////

	num_printf = printf("char: %c", c);
	printf("\n");
	num_chars = ft_printf("char: %c", c);
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf("str: %s", str);
	printf("\n");
	num_chars = ft_printf("str: %s", str);
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf("strNULL: %s", NULL);
	printf("\n");
	num_chars = ft_printf("strNULL: %s", NULL);
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf("p_ok: %p", puntero);
	printf("\n");
	num_chars = ft_printf("p_ok: %p", puntero);
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf("p_null: %p", punt_null);
	printf("\n");
	num_chars = ft_printf("p_null: %p", punt_null);
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf("nums: %d %i", num_dec, num_zero);
	printf("\n");
	num_chars = ft_printf("nums: %d %i", num_dec, num_zero);
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf("Max_int: %i %d ", max_int, max_intplus);
	printf("\n");
	num_chars = ft_printf("Max_int: %i %d ", max_int, max_intplus);
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf("Min_int: %i %d ", min_int, min_intplus);
	printf("\n");
	num_chars = ft_printf("Min_int: %i %d ", min_int, min_intplus);
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf("hex: %x %X", min_int, min_intplus);
	printf("\n");
	num_chars = ft_printf("hex: %x %X", min_int, min_intplus);
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf("unsig: %u %u", max_unsigned, max_unsignedPlus);
	printf("\n");
	num_chars = ft_printf("unsig: %u %u", max_unsigned, max_unsignedPlus);
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf(" %%   %%   %% ");
	printf("\n");
	num_chars = ft_printf(" %%   %%   %% ");
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf("char: %c str: %s strNull: %s punt: %p PuntNull: %p, num: %d, %% unsig: %u hex: %x HEX: %X adios", c, str, NULL, puntero, punt_null, num_dec, max_unsigned, min_int, min_intplus);
	printf("\n");
	num_chars = ft_printf("char: %c str: %s strNull: %s punt: %p PuntNull: %p, num: %d, %% unsig: %u hex: %x HEX: %X adios", c, str, NULL, puntero, punt_null, num_dec, max_unsigned, min_int, min_intplus);
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");


/////////////////////////////////////////////
///INVALIDOS
////////////////////////////////////////////

	num_printf = printf("patata %D lechuga %H patata %J bc %k tomate %K");
	printf("\n");
	num_chars = ft_printf("patata %D lechuga %H patata %J bc %k tomate %K");
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf("patata %h lechuga %j patata %l bc %L tomate %q adios");
	printf("\n");
	num_chars = ft_printf("patata %h lechuga %j patata %l bc %L tomate %q adios");
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf("patata%h cebolla %d", num_dec);
	printf("\n");
	num_chars = ft_printf("patata%h cebolla %d", num_dec);
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf("patata%");
	printf("\n");
	num_chars = ft_printf("patata%");
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	num_printf = printf("patata%C lechuga");
	printf("\n");
	num_chars = ft_printf("patata%C lechuga");
	printf("\nNumChars: %d | %d", num_printf, num_chars);

	printf("\n\n");

	free (puntero);
	return (0);
}
