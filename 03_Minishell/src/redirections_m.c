/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:26:18 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/19 13:14:29 by mpico-bu         ###   ########.fr       */
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

void	handle_all_redirections(t_input *input)
{
	size_t	i = 0;
	bool	single_quote = false;
	bool	double_quote = false;

	while (input->input[i])
	{
		if (input->input[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (input->input[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if (!single_quote && !double_quote)
		{
			if (input->input[i] == '>' && input->input[i + 1] == '>')
			{
				handle_append_redirection(input, &input->input[i]);
				i++;
			}
			else if (input->input[i] == '<' && input->input[i + 1] == '<')
			{
				handle_heredoc_redirection(input, &input->input[i]);
				i++;
			}
			else if (input->input[i] == '>')
				handle_output_redirection(input, &input->input[i]);
			else if (input->input[i] == '<')
				handle_input_redirection(input, &input->input[i]);
		}
		i++;
	}
}
void	handle_redirection(t_input *input)
{
	size_t	i = 0;
	bool	single_quote = false;
	bool	double_quote = false;

	while (input->input[i])
	{
		if (input->input[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (input->input[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if (!single_quote && !double_quote)
		{
			if (input->input[i] == '>' && input->input[i + 1] == '>')
			{
				handle_append_redirection(input, &input->input[i]);
				i++;
			}
			else if (input->input[i] == '<' && input->input[i + 1] == '<')
			{
				handle_heredoc_redirection(input, &input->input[i]);
				i++;
			}
			else if (input->input[i] == '>')
				handle_output_redirection(input, &input->input[i]);
			else if (input->input[i] == '<')
				handle_input_redirection(input, &input->input[i]);
		}
		i++;
	}
}

