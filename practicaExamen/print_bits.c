/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:38:08 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/07 10:54:32 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*takes a byte and prints its binary without \n*/

#include <unistd.h>

void	print_bits(unsigned char octet)
{
	unsigned char	masc;
	unsigned char	byte;	
	size_t			i;

	masc = 0x80;
	i = 0;
	while (i < 8)
	{
		byte = octet & masc;
		if (byte == 0)
			write(1, "0", 1);
		else
			write(1, "1", 1);
		masc >>= 1;
		i++;
	}	
}

int main()
{
	print_bits(2);
	write (1, "\n", 1);
	print_bits(0x80);
	return 0;
	
}

