/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:19:50 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/07 11:33:45 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
unsigned char	swap_bits(unsigned char octet)
{
	unsigned char	r_masc;
	unsigned char	m_masc;
	unsigned char	solution;
	size_t			i;

	m_masc = 16;
	r_masc	= 0x01;
	solution = 0x0;
	i = 0;
	while (i < 4)
	{
		if (octet & m_masc)
			solution |= r_masc;
		if (octet & r_masc)
			solution |= m_masc;
		m_masc <<= 1;
		r_masc <<= 1;
		i++;
	}
	return (solution);
}

#include <stdio.h>
int	main(void)
{
	printf("%d\n", swap_bits(65));	
	return 0;
}
