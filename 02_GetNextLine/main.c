/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:18:57 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/30 23:29:08 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*linea;

	/* if (argc != 2)
		return (1); */
	(void)argc;
	(void)argv;
	fd = open("TEST/dib4.txt", O_RDONLY);
	if (fd == -1)
		write(2, "Error reading\n", 14);
	
	for (size_t i = 0; i < 20; ++i)
	{
		linea = get_next_line(fd);
		printf("%s", linea);
	}
	
	/* linea = get_next_line(fd);
	printf("\nLinea: %s", linea);
	 */close(fd);
	return (0);
}
