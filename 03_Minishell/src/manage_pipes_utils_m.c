/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:32:40 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/30 01:28:06 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

char	*join_command(char **split_exp, int start, int end)
{
	int		i;
	size_t	len;
	char	*joined;

	len = 0;
	i = start;
	while (i < end)
		len += ft_strlen(split_exp[i++]) + 1;
	joined = malloc(len + 1);
	if (!joined)
		return (NULL);
	joined[0] = '\0';
	i = start;
	while (i < end)
	{
		ft_strcat(joined, split_exp[i]);
		if (i < end - 1)
			ft_strcat(joined, " ");
		i++;
	}
	return (joined);
}

int	count_pipes(t_input *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input->split_exp && input->split_exp[i])
	{
		if (ft_strcmp(input->split_exp[i], "|") == 0
			&& input->status_exp[i] == 0)
			count++;
		i++;
	}
	return (count);
}

void	ft_compose_parsed(t_input *input)
{
	int		i;
	bool	first;

	i = 0;
	first = true;
	input->parsed = ft_strdup("");
	while (input->input_split && input->input_split[i])
	{
		if (ft_strcmp(input->input_split[i], input->command) == 0)
		{
			i++;
			continue ;
		}
		if (!first)
			input->parsed = ft_strjoin_r(input->parsed, " ");
		input->parsed = ft_strjoin_r(input->parsed, input->input_split[i]);
		first = false;
		i++;
	}
	input->parsed = ft_strjoin_r(input->parsed, "\0");
}

void	setup_pipe(int *pipefd, int cmd, int num_cmds)
{
	if (cmd < num_cmds - 1 && pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	handle_fork_error(void)
{
	perror("fork");
	exit(EXIT_FAILURE);
}
