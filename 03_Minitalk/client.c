/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:54:07 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/28 14:02:44 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

unsigned char	process_char(char c)
{
	size_t			i;
	unsigned char	masc;
	unsigned char	solution;
	
	i = 0;
	masc = 0x01;
	solution = 0x0;
	while (i < 8)
	{
		if (c & masc)
			solution = solution | masc;
		masc <<= 1;	
		i++;
	}
	return (solution);
}

void	process_msg(char *msg)
{
	unsigned char	solution;
	size_t			i;

	/*he de hacer un malloc con strlen(msg) * 8 (nmero de bytes por 1 byte) y a partir de entonces meter cada letra en ese malloc para luego soltarlo todo*/
	/*para dos chars: unsigned char bits[16];
	bits[i] = (c1 & (0x80 >> i)) ? 1 : 0; es ternario no vale. pero se entiende la idea.
	*/
	while (msg[i])
	{
		process_char(msg[i]);
		i++;
	}	
}

int	main(int ac, char **av)
{
	pid_t	pid;
	
	if (ac != 3)
		return (ft_printf("Error:\nNeed: './client PID \"string\"'\n"), 1);
	pid = ft_atoi(av[1]);
	if (kill(pid, 0) == -1)
		return (ft_printf("Error:\nNot a valid PID or Comm not allowed\n"), 1);
	process_msg(av[2]);
	return (0);
	
}
