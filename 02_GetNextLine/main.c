/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:18:57 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/09 22:37:38 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*linea;
	int		flag = 1;
	int		i = 0;

	/* if (argc != 2)
		return (1); */
	(void)argc;
	(void)argv;
	linea = NULL;
	fd = open("TEST/1char.txt", O_RDONLY);
	if (fd == -1)
		write(2, "Error reading\n", 14);

	while (linea || flag)
	{
		linea = NULL;
		flag = 0;
		linea = get_next_line(fd);
		if (linea)
		{
			printf("%s", linea);
		//	printf("\n");
		}
		free (linea);
		i++;
	}

	/* linea = get_next_line(fd);
	printf("\nLinea: %s", linea);
	 */close(fd);
	return (0);
}
