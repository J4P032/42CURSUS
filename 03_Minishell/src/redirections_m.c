/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:26:18 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/24 01:43:50 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void remove_redirections_from_input(t_input *input)
{
	char	*clean_input;
	size_t	i = 0, j = 0;
	bool	sq = false, dq = false;

	clean_input = malloc(ft_strlen(input->input) + 1);
	while (input->input[i])
	{
		if (input->input[i] == '\'' && !dq)
			sq = !sq;
		else if (input->input[i] == '"' && !sq)
			dq = !dq;
		else if (!sq && !dq && (input->input[i] == '<' || input->input[i] == '>'))
		{
			size_t skip = 1;
			if (input->input[i + 1] == '<' || input->input[i + 1] == '>')
				skip++;
			i += skip;
			while (input->input[i] == ' ')
				i++;
			while (input->input[i] && input->input[i] != ' ' && input->input[i] != '<' && input->input[i] != '>')
			{
				if (input->input[i] == '"' || input->input[i] == '\'')
					break;
				i++;
			}
			continue;
		}
		clean_input[j++] = input->input[i++];
	}
	clean_input[j] = '\0';
	free(input->input);
	input->input = clean_input;
}


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
	if ((filename[0] == '"' && end[0] == '"') || (filename[0] == '\'' && end[0] == '\''))
	{
		filename++;
		end--;
		*end = '\0';
	}
	while (end > filename && (*end == ' ' || *end == '\n'))
		*end-- = '\0';
	input->inputfd = open(filename, O_RDONLY);
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
bool	handle_redirection(t_input *input)
{
	char	*last_in = NULL;
	char	*last_out = NULL;
	char	*last_append = NULL;
	size_t	i = 0;
	bool	sq = false, dq = false;

	while (input->input[i])
	{
		if (input->input[i] == '\'' && !dq)
			sq = !sq;
		else if (input->input[i] == '"' && !sq)
			dq = !dq;
		else if (!sq && !dq)
		{
			if (input->input[i] == '<' && input->input[i + 1] != '<')
				last_in = &input->input[i];
			else if (input->input[i] == '>' && input->input[i + 1] == '>')
				last_append = &input->input[i];
			else if (input->input[i] == '>' && input->input[i + 1] != '>')
				last_out = &input->input[i];
		}
		i++;
	}

	if (last_in)
		handle_input_redirection(input, last_in);
	if (last_append)
		handle_append_redirection(input, last_append);
	else if (last_out)
		handle_output_redirection(input, last_out);

	remove_redirections_from_input(input);
	return (0);
}
