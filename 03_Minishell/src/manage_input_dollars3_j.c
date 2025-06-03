/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input_dollars3_j.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:12:04 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/02 10:26:24 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	do_even_dollars2(t_input *in, size_t w, size_t *i, size_t *k)
{
	in->spaced = 1;
	while (in->input_split[w][*i] && in->input_split[w][*i] != '?')
		in->command[(*k)++] = in->input_split[w][(*i)++];
}

void	env_question2(t_input *in, size_t w, size_t *i, size_t *k)
{
	while (in->input_split[w][*i] && in->input_split[w][(*i) + 1] != ' '
		&& in->input_split[w][*i] != '$')
	{
		dynamic_command(in, *k);
		in->command[(*k)++] = in->input_split[w][(*i)++];
	}
}

void	input_check_prev_dollar(t_input *in, size_t *i, size_t *j, size_t *k)
{
	if (in->input_split[*i][*j] && in->input_split[*i][*j] != '$')
	{
		dynamic_command(in, *k);
		if (*j > 0 && in->input_split[*i][*j] == ' '
			&& in->input_split[*i][(*j) - 1] == '$')
			in->command[(*k)++] = in->input_split[*i][(*j)];
		(*j)++;
	}
}

void	save_env_if_even_dollars2(t_input *in, size_t w, size_t *i, size_t *k)
{
	while (in->input_split[w][*i] && in->input_split[w][(*i) + 1] != ' ')
	{
		(*i)++;
		dynamic_command(in, *k);
		in->command[(*k)++] = in->input_split[w][(*i)];
	}
}

void	save_rare_cases2(t_input *in, size_t *k, char *str, size_t id)
{
	in->command[(*k)++] = '$';
	dynamic_command(in, *k);
	in->command[(*k)++] = str[id];
}
