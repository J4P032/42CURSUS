/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:50:09 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/02 14:33:08 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*we can have arguments as push_swap 3 4 5 ... or push_swap 3 4 "2 5" 8*/
/*inside compose_stack we will return 0 no error, 1 = error of invalid argvs*/
/*counting_sort will assign final ordering index to each number. How ends.*/
/*ordering initializes de ordering based in ordered index asigned*/
int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	a = NULL;
	b = NULL;
	if (compose_stack_a(&a, argc, argv))
	{
		write (1, "Error\n", 6);
		return (1);
	}
	if (!a)
	{
		argv = NULL;
		return (1);
	}
	counting_sort(a);
	ordering(&a, &b);
	ft_free((void **)&a, 1);
	ft_free((void **)&b, 1);
	return (0);
}
