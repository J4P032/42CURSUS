/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:05:48 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/21 03:52:51 by mpico-bu         ###   ########.fr       */
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
	input->input_split = NULL; //hacer ft_matrix_free *** y asi podre asignar ahi el NULL
	if (input->envp) //si error = 0 deberia eliminarlo?
		ft_matrix_free(input->envp);
	input->envp = NULL; //hacer ft_matrix_free *** y asi podre asignar ahi el NULL
	if (input->local_envp)
		ft_matrix_free(input->local_envp);
	input->local_envp = NULL;
	if (input->split_exp)
		ft_matrix_free(input->split_exp);
	input->split_exp = NULL; //hacer ft_matrix_free *** y asi podre asignar ahi el NULL
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
