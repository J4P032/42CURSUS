/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:26:18 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/09 01:27:48 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	handle_redirection(t_input *input)
{
	char	*redir;

	if ((redir = ft_strnstr(input->input, ">>", ft_strlen(input->input))))
	{
		*redir = '\0';
		redir += 2;
		while (*redir == ' ')
			redir++;
		input->outputfd = open(redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (input->outputfd < 0)
			perror("open append");
	}
	else if ((redir = ft_strchr(input->input, '>')))
	{
		*redir = '\0';
		redir++;
		while (*redir == ' ')
			redir++;
		input->outputfd = open(redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (input->outputfd < 0)
			perror("open output");
	}
	else if ((redir = ft_strchr(input->input, '<')))
	{
		*redir = '\0';
		redir++;
		while (*redir == ' ')
			redir++;
		input->inputfd = open(redir, O_RDONLY);
		if (input->inputfd < 0)
			perror("open input");
	}
}

