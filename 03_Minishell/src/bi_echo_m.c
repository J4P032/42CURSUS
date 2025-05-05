/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo_m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:50:16 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/05 20:49:18 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

/*start is because the first argument from the command or the -n even it is...*/
/*...spaced it dont have to space it when printed.*/
void	ft_echo(t_input *in)
{
	size_t	i;
	size_t	n_repeated;
	int		argument;
	size_t	start;
	
	i = 1;
	n_repeated = 1;
	while (in->args[i])
	{
		if (in->args[i++] != 'n')
			n_repeated = 0;
	}
	argument = ft_strncmp(in->args, "-n", 2);
	if (argument == 0 && n_repeated)
		i = in->word_after_arg;
	else
		i = in->word_after_command;
	start = i;
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
	if (argument != 0)
		printf("\n");
}
