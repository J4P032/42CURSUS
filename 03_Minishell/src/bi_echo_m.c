/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo_m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:50:16 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/06 17:05:33 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

size_t	check_rest_of_n(t_input *in)
{
	size_t	i;
	size_t	j;
	size_t	n_repeated;

	n_repeated = 1;
	j = in->word_after_arg;
	while (j < in->input_words)
	{
		i = 1;
		compose_arg(in, j);
		while (in->args[i] && n_repeated)
		{
			if (in->args[0] != '-' || in->args[i++] != 'n')
				n_repeated = 0;
		}
		if (ft_strncmp(in->args, "-n", 2) != 0)
			n_repeated = 0;
		if (n_repeated == 0)
			break ;
		j++;
	}
	return (j);
}

size_t	give_me_the_fist_word(t_input *in, int *error_argument)
{
	size_t	i;
	size_t	n_repeated;

	i = 1;
	n_repeated = 1;
	while (in->args[i])
	{
		if (in->args[i++] != 'n' || in->args[0] != '-')
		{
			n_repeated = 0;
			*error_argument = 1;
		}
	}
	if (ft_strncmp(in->args, "-n", 2) != 0)
		*error_argument = 1;
	if (*error_argument == 0 && n_repeated)
		i = check_rest_of_n(in);
	else
		i = in->word_after_command;
	return (i);
}

/*start is because the first argument from the command or the -n even it is...*/
/*...spaced it dont have to space it when printed.*/
void	ft_echo(t_input *in)
{
	size_t	i;
	size_t	start;
	int		error_argument;

	error_argument = 0;
	start = give_me_the_fist_word(in, &error_argument);
	i = start;
	while (i < in->input_words && in->input_split && in->input_split[i])
	{
		if ((in->status[i] == EPTY_SP || in->status[i] == SQUO_SP
				|| in->status[i] == DQUO_SP) && in->input_split[i][0]
				&& i != start)
			printf(" %s", in->input_split[i]);
		else if ((in->status[i] == EPTY_SP || in->status[i] == SQUO_SP
				|| in->status[i] == DQUO_SP) && in->input_split[i][0] == '\0'
				&& i != start)
			printf(" ");
		else if (in->input_split[i][0])
			printf("%s", in->input_split[i]);
		i++;
	}
	if (error_argument == 1)
		printf("\n");
}
