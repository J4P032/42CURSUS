/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:11:38 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/07 11:15:10 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char	left_masc;
	unsigned char	right_masc;
	unsigned char	solution;
	size_t			i;

	left_masc = 0x80;
	right_masc = 0x01;
	solution = 0x0;
	i = 0;
	while (i < 4)
	{
		if (octet & left_masc)
			solution = solution | right_masc;
		if (octet & right_masc)
			solution = solution | left_masc;
		left_masc >>= 1;
		right_masc <<= 1;
		i++;
	}
	return (solution);
}
#include <stdio.h>
int	main(void)
{
	printf("%d\n", reverse_bits(32));	
	return 0;
}
