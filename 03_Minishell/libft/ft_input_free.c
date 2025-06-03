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

#include "../inc/minishell_j.h"
#include "../inc/minishell_m.h"
#include "libft.h"

void	ft_input_null(t_input *input)
{
	int	i;

	if (!input)
		return ;
	i = 0;
	input->input = NULL;
	input->status = NULL;
	input->token = NULL;
	input->command = NULL;
	input->filename = NULL;
	input->parsed = NULL;
	input->args = NULL;
	input->input_split = NULL;
	input->split_exp = NULL;
	while (i++ < 100)
		input->status_exp[i] = 0;
	input->cmd = 0;
	input->cmd_start = 0;
	input->cmd_end = 0;
}

void	ft_input_free(t_input *input)
{
	if (input->input)
		free(input->input);
	if (input->status)
		free(input->status);
	if (input->token)
		free(input->token);
	if (input->command)
		free(input->command);
	if (input->filename)
		free(input->filename);
	if (input->parsed)
		free(input->parsed);
	if (input->args)
		free(input->args);
	if (input->input_split)
		ft_matrix_free(&input->input_split);
	if (input->split_exp)
		ft_matrix_free(&input->split_exp);
	ft_input_null(input);
}
