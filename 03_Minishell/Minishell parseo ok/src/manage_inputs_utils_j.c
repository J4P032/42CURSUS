/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_inputs_utils_j.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:31:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/17 17:07:07 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	search_dollar(t_input *in, size_t *i, size_t *j, size_t *k)
{
	int	print_as_env;

	print_as_env = (is_quoted(in, *i) == 2 || !is_quoted(in, *i));
	if (ft_strrchr(in->input_split[*i], '$') && print_as_env)
		expand_dollar(in, i, j, k);
	else
		in->command[(*k)++] = in->input_split[*i][(*j)++];
}

/*Do the same as copy_to_command BUT it starts from the token that was left...*/
/*...after the command. The token after the argument is behaved the...*/
/*...same as the first token in echo (no spaced unless quoted with space)...*/
/*...then we have to do the same with i < in this case word (after command)*/
void	copy_to_arg(t_input *in, size_t *i, size_t *j, size_t *k)
{
	while (*i < in->input_words)
	{
		*j = 0;
		in->status_checked = 0;
		if (*i > in->word && in->input_split[*i][0] == '\0'
			&& (in->status[*i] == SQUO_SP || in->status[*i] == DQUO_SP))
			break ;
		while ((in->input_split[*i][*j] != ' ' || is_quoted(in, *i))
			&& in->input_split[*i][*j] != '\0' && !in->spaced)
		{
			if ((*i > in->word && (in->status[*i] == EPTY_SP
						|| in->status[*i] == SQUO_SP
						|| in->status[*i] == DQUO_SP)
					&& !in->status_checked))
				in->spaced = 1;
			else
				in->args[(*k)++] = in->input_split[*i][(*j)++];
			in->status_checked = 1;
		}
		if (in->input_split[*i][*j] == ' ' || in->spaced)
			break ;
		(*i)++;
	}
}

/*first if will stop copy when find a '' or "" that is previously spaced...*/
/*...if that token is not the first one as the first one will be always...*/
/*...spaced (because it is an argument). Could be (echo ''''-n'' example) */
/*The while inside will queck parts in quotes without space. If find an...*/
/*...space in the quotes will finish copy (echo '- n' -> no valid)...*/
/*...the if inside the internal while is a flag (in->spaced)to exit in...*/
/*...the botton if. Again i must be not the first word as it is spaced*/
void	copy_to_command(t_input *in, size_t *i, size_t *j, size_t *k)
{
	while (*i < in->input_words)
	{
		*j = 0;
		in->status_checked = 0;
		if (*i > 0 && in->input_split[*i][0] == '\0'
			&& (in->status[*i] == SQUO_SP || in->status[*i] == DQUO_SP))
			break ;
		while ((in->input_split[*i][*j] != ' ' || is_quoted(in, *i))
			&& (in->input_split[*i][*j] != '\0') && !in->spaced)
		{
			if (*i > 0 && (in->status[*i] == EPTY_SP
					|| in->status[*i] == SQUO_SP
					|| in->status[*i] == DQUO_SP)
				&& !in->status_checked)
				in->spaced = 1;
			else
				search_dollar(in, i, j, k);
			in->status_checked = 1;
		}
		if (in->input_split[*i][*j] == ' ' || in->spaced)
			break ;
		(*i)++;
	}
}

void	compose_arg(t_input *in, size_t word)
{
	size_t	i;
	size_t	j;
	size_t	k;

	k = 0;
	i = word;
	in->word = word;
	in->spaced = 0;
	in->status_checked = 0;
	ft_bzero(in->args, 100000);
	copy_to_arg(in, &i, &j, &k);
	in->word_after_arg = i;
}

void	compose_command_args(t_input *in)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	in->spaced = 0;
	in->status_checked = 0;
	ft_bzero(in->command, 100000);
	copy_to_command(in, &i, &j, &k);
	in->word_after_command = i;
	compose_arg(in, i);
}
