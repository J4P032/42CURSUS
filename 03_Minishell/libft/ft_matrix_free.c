/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:09:14 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/14 17:40:09 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/minishell_j.h"

void	ft_matrix_free(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	ft_input_free(t_input *input)
{
	int	i;

	i = 0;
	while (input->input_split && input->input_split[i])
	{
		free(input->input_split[i]);
		input->input_split[i] = NULL;
		i++;
	}
	if (input->input_split)
		free(input->input_split);
	input->input_split = NULL;
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
