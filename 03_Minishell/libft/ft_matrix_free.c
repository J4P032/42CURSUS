/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:09:14 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/20 20:14:32 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/minishell_j.h"

void	ft_matrix_free(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	if (matrix)
		free(matrix);
}

void	ft_input_free(t_input *input)
{
	ft_matrix_free(input->input_split);
	input->input_split = NULL;
	ft_matrix_free(input->split_exp);
	input->split_exp = NULL;
	if (input->status)
		free(input->status);
	input->status = NULL;
	if (input->filename)
		free(input->filename);
	input->filename = NULL;
	if (input->parsed)
		free(input->parsed);
	input->parsed = NULL;
}
