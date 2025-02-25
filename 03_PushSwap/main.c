/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:50:09 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/25 19:15:19 by jrollon-         ###   ########.fr       */
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
	t_stack	*aux;

	a = NULL;
	b = NULL;
	if ((argc == 1) || (argc == 2 && !argv[1][0]))
	{
		write (1, "Error\n", 6);
		return (1);
	}
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
	aux = a;
	while (aux && aux->next)
	{
		printf("%d\n", aux->value); ///
		aux = aux->next;
	}
	if (aux)
		printf("%d\n", aux->value);

	//move_swap(&a, 'a');
	move_push(&a, &b);
	move_push(&a, &b);
	printf("\n");//
	aux = a;
	while (aux && aux->next)
	{
		printf("%d\n", aux->value); ///
		aux = aux->next;
	}
	if (aux)
		printf("%d\n", aux->value);

	ft_free((void **)&a, 1);
	ft_free((void **)&b, 1);
	return (0);
}
