/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:09:14 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/30 00:09:53 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/minishell_j.h"

void	ft_matrix_free(char ***matrix)
{
	int	i;

	i = 0;
	if (!matrix || !*matrix)
		return ;
	while ((*matrix)[i])
	{
		if ((*matrix)[i])
			free((*matrix)[i]);
		(*matrix)[i] = NULL;
		i++;
	}
	free((*matrix));
	*matrix = NULL;
}

void	ft_input_free(t_input *input)
{
	ft_matrix_free(&input->input_split);
	ft_matrix_free(&input->split_exp);
	if (input->input)
		free(input->input);
	input->input = NULL;
	if (input->status)
		free(input->status);
	input->status = NULL;
	if (input->token)
		free(input->token);
	input->token = NULL;
	if (input->command)
		free(input->command);
	input->command = NULL;
	if (input->filename)
		free(input->filename);
	input->filename = NULL;
	if (input->parsed)
		free(input->parsed);
	input->parsed = NULL;
	if (input->args)
		free(input->args);
	input->args = NULL;
	for(size_t i = 0; input->status_exp[i]; i++)
		input->status_exp[i] = 0;
	if (input->split_exp)
	{
		ft_matrix_free(&input->split_exp);
		input->split_exp = NULL;
	}
}

