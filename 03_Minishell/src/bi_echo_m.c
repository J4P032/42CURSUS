/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo_m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:50:16 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/05 18:17:40 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	ft_echo(t_input *in)
{
	size_t	i;
	int		argument;
	size_t	start;
	
	argument = ft_strcmp(in->args, "-n");
	if (argument == 0)
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
