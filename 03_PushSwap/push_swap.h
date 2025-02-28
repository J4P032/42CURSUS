/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:51:50 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/28 21:56:00 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
#include <unistd.h>

#include "libft/libft.h"

typedef struct s_stack
{
	int				value;
	size_t			index;
	struct s_stack	*prev;
	struct s_stack	*next;
}					t_stack;

int			compose_stack_a(t_stack **stack, int argc, char **argv);
long int	ps_atol(char *nptr, int *error);
int			ft_free(void **item, int option);
void		move_swap(t_stack **stack, char c);
void		double_swap(t_stack **stack1, t_stack **stack2);
void		move_push(t_stack **stack1, t_stack **stack2, char c);
void		simulate_push(t_stack **stack1, t_stack **stack2, size_t *moves);
void		move_rotate(t_stack **stack, char c);
void		move_inv_rotate(t_stack **stack, char c);
void		simulate_inv_rotate(t_stack **stack, size_t *moves);
void		simulate_rotate(t_stack **stack, size_t *moves);
void		double_rotate(t_stack **stack1, t_stack **stack2);
void		double_inv_rotate(t_stack **stack1, t_stack **stack2);
void		counting_sort(t_stack *stack);
void		ksort(t_stack **a, t_stack **b, size_t chunck);
void		sim_ksort(t_stack **a, t_stack **b, size_t chunck, size_t *moves);
void		sim_order(t_stack **a, t_stack **b, size_t s_index, size_t *moves);
void		checker_value(t_stack **aux, t_stack *node, int value, int *error);
int     	ft_sqrt(int nb);
void		ordering(t_stack **a, t_stack **b);
size_t		stacksize(t_stack *stack);
size_t		brute_force(t_stack *a, t_stack **b, size_t nodes);
t_stack		*last_node(t_stack *stack);
void		normal_sort(t_stack **a, t_stack **b, size_t nodes);

#endif
