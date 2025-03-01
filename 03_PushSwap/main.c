/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:50:09 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/01 12:55:52 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h> //

/*can pass numbers between "..." so 2 argc or without so more argc*/
/*if is "..." I make split to have the arguments and save new argv*/
/*if not "..." just call the compose_stack_a function with full argv*/
int	main(int argc, char **argv)
{
	t_stack *a;
	t_stack *b;

	a = NULL;
	b = NULL;
/* 	if (argc == 2 && !argv[1][0])
	{
		write (1, "Error\n", 6);
		return (1);
	} */
	if (compose_stack_a(&a, argc, argv))
	{
		write (1, "Error\n", 6);
		return (1);
	}
	if (!a) //cuando falla la composicion del stack
	{
		argv = NULL; //lo ha liberado dentro de compose_stack
		return (1);
	}
	counting_sort(a);
	ordering(&a, &b);
	//ksort(&a, &b);
	ft_free((void **)&a, 1);
	ft_free((void **)&b, 1);
	return (0);
}
