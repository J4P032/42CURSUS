/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_m.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:53:26 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/06/03 10:07:55 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

static void	init_input_struct_null(t_input *input)
{
	input->filename = NULL;
	input->parsed = NULL;
	input->input_split = NULL;
	input->split_exp = NULL;
	input->status = NULL;
	input->token = NULL;
	input->command = NULL;
	input->args = NULL;
}

void	init_input_struct(t_input *input)
{
	init_input_struct_null(input);
	input->word_after_command = 0;
	input->word_after_arg = 0;
	input->input_words = 0;
	input->word = 0;
	input->dollars = 0;
	input->idollar = 0;
	input->env_len = 0;
	input->last_exit_code = 0;
	input->realloc_counter = 0;
	input->from_expand = 0;
	input->inputfd = STDIN_FILENO;
	input->outputfd = STDOUT_FILENO;
	input->total_pipes = 0;
	input->total_redirections = 0;
	input->cmd_start = 0;
	input->num_cmds = 0;
}
