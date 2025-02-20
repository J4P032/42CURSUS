/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:50:09 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/20 13:21:52 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h> ///

int	main(int argc, char **argv)
{
	size_t i;
	
	i = 0;
	if ((1 == argc) || (2 == argc && !argv[1][0]))
		return (1);
	if (2 == argc)
		argv = ft_split(argv[1], ' ');
	while (argv)
		printf("%s\n", argv[i]);
	free (argv);
	argv = NULL;
	return (0);
}
