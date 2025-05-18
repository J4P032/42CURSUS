/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:05:48 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/18 18:03:48 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	clean_all(t_input *input, int error)
{
	ft_manage_history(NULL, 1);
	if (input->input)
	{
		free(input->input);
		input->input = NULL;
	}
	if	(input->input_split)
		ft_matrix_free(input->input_split);
	if (input->envp)
		ft_matrix_free(input->envp);
	if (input->status)
	{
		free(input->status);
		input->status = NULL;
	}
	if (input->parsed)
	{
		free(input->parsed);
		input->parsed = NULL;
	}
	if (error)
		rl_clear_history();
	if (error)
		exit(error);
}
