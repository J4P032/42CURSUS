/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:26:18 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/13 19:07:50 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

static void	handle_append_redirection(t_input *input, char *redir)
{
	char	*filename;
	char	*end;

	*redir = '\0';
	redir += 2;
	while (*redir == ' ')
		redir++;
	filename = ft_strdup(redir);
	end = filename + ft_strlen(filename) - 1;
	while (end > filename && (*end == ' ' || *end == '\n'))
		*end-- = '\0';
	input->outputfd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (input->outputfd < 0)
		perror("open append");
	free(filename);
}

static void	handle_output_redirection(t_input *input, char *redir)
{
	char	*filename;
	char	*end;

	*redir = '\0';
	redir++;
	while (*redir == ' ')
		redir++;
	filename = ft_strdup(redir);
	end = filename + ft_strlen(filename) - 1;
	while (end > filename && (*end == ' ' || *end == '\n'))
		*end-- = '\0';
	input->outputfd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (input->outputfd < 0)
		perror("open output");
	free(filename);
}

static void	handle_input_redirection(t_input *input, char *redir)
{
	char	*filename;
	char	*end;

	*redir = '\0';
	redir++;
	while (*redir == ' ')
		redir++;
	filename = ft_strdup(redir);
	end = filename + ft_strlen(filename) - 1;
	while (end > filename && (*end == ' ' || *end == '\n'))
		*end-- = '\0';
	input->inputfd = open(filename, O_RDONLY);
	if (input->inputfd < 0)
		perror("open input");
	free(filename);
}

void	handle_redirection(t_input *input)
{
	char	*redir;

	redir = ft_strnstr(input->input, ">>", ft_strlen(input->input));
	if (redir)
		handle_append_redirection(input, redir);
	else
	{
		redir = ft_strnstr(input->input, "<<", ft_strlen(input->input));
		if (redir)
			handle_heredoc_redirection(input, redir);
		else
		{
			redir = ft_strnstr(input->input, ">", ft_strlen(input->input));
			if (redir)
				handle_output_redirection(input, redir);
			else
			{
				redir = ft_strnstr(input->input, "<", ft_strlen(input->input));
				if (redir)
					handle_input_redirection(input, redir);
			}
		}
	}
}
