/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:54:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/28 13:09:10 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*function free an stack or argv from split*/
int	ft_free(void **item, int option)
{
	t_stack	*aux;
	t_stack *stack;
	char	**str;

	if (!item || !*item)
		return (1);
	if (1 == option)
	{
		stack = (t_stack *)*item;
		while (stack)
		{
			aux = (stack)->next;
			free(stack);
			stack = aux;
		}
		return (*item = NULL, 1) ;
	}
	str = (char **)*item;
	while (*str)
	{
		free(*str);
		*str = NULL;
		str++;
	}
	return (free (*item), 1);
}

void	free_all(t_stack **stack, char **argv)
{
	ft_free((void **)stack, 1);
	ft_free((void **)&argv, 0);
}

/*list is double side (previous and next)*/
/*if "new" number is found in existing nodes error = 1 & I will free all out*/
void	create_node(t_stack **stack, t_stack *node, int value, int *error)
{
	t_stack	*aux;

	aux = NULL;
	node->value = value;
	if ((!*stack))
	{
		node->next = NULL;
		node->prev = NULL;
		*stack = node;
		return ;
	}
	aux = *stack;
	checker_value(&aux, node, value, error);
	if (*error)
		return ;
	aux->next = node;
	node->next = NULL;
	node->prev = aux;
}

/*convert the number string into a valid number (if error remains 0)*/
/*then store the number in a node and add it to the list (stack)*/
/*if in any case error = 1 I will free all stack, node and argv from split*/
/*finally if all is stored correctly I free all split argv numbers*/
void	store_number(t_stack **stack, char **argv, int *error)
{
	long int	number;
	t_stack		*node;
	char		**aux;

	node = NULL;
	aux = argv;
	while (*aux)
	{
		number = ps_atol(*aux, error);
		node = ft_calloc(1, sizeof(t_stack));
		if (!node || *error)
		{
			free_all(stack, argv);
			free(node); //SI ES POR ERROR QUE VIENE DEL NUMBER HAY QUE LIBERAR EL NODO.CHEQUEAR QUE ESTA BIEN!!!
			*error = 1; //por si entra por fallo de node para no liberar dos veces fuera
			return ;
		}
		create_node (stack, node, number, error);
		if (*error)
		{
			free_all(stack, argv);
			return ;
		}
		aux++;
	}
}

/*Returns error. 0 = OK. 1 = error*/
/*if numbers in "..." I call store_number from argv[0]*/
/*if numbers not in "..." call store_number without the name program*/
/*there is an error to check in all functions any error to change to 1*/
int	compose_stack_a(t_stack **stack, int argc, char **argv)
{
	int		error;
	char	**aux;
	char	**temp;

	(void)argc;
	error = 0;
	aux = argv + 1;
	while (*aux)
	{
		temp = ft_split(*aux, ' '); //mirar si es correcto el aux =
		if (!temp)
		{
			ft_free((void **)stack, 1);
			//free_all(stack, aux); //modificado argv por aux
			return (error);
		}
		store_number(stack, temp, &error);
		if (!error)
			ft_free((void **)&temp, 0);
		if (error)
			return (error);
		aux++;
	}
	return (error);
}
