/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:50:09 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/20 19:34:03 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*can pass numbers between "..." so 2 argc or without so more argc*/
/*if is "..." I make split to have the arguments and save new argv*/
/*if not "..." just call the compose_stack_a function with full argv*/
int	main(int argc, char **argv)
{
	t_stack *a;
	t_stack *b;
		
	a = NULL;
	b = NULL;	
	if ((argc == 1) || (argc == 2 && !argv[1][0]))
	{
		write (1, "Error\n", 6);
		return (1);
	}
	if (argc == 2)
		argv = ft_split(argv[1], ' ');
	if (compose_stack_a(&a, argc, argv))
	{
		write (1, "Error\n", 6);
		return (1);
	}
	
	
	free (argv);
	argv = NULL;
	return (0);
}
