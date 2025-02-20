/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:54:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/20 14:35:56 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_build(t_stack **stack, char **argv)
{
	*stack = ft_calloc(1, sizeof(t_stack));
	if (!stack)
		return ; //si no lo hace salto y en la llamada ya libero argv si o si. No hace falta liberar nada pues.
	//CHEQUEAR ERRORES DE ARGV
	
}


void	compose_stack_a(int argc, char **argv)
{
	t_stack	*a;
	t_stack *b;
	
	a = NULL;
	b = NULL;
	if (2 == argc)
	{
		stack_build(&a, argv);
		free (argv);
		argv = NULL;
	}
	else
		stack_build(&a, argv + 1);
	
	
}
