/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:26:18 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/10 01:23:54 by mpico-bu         ###   ########.fr       */
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

static void	handle_heredoc_redirection(t_input *input, char *redir)
{
	char	*delim;
	char	*end;
	char	*buffer;
	char	line[1024];
	int		pipefd[2];

	*redir = '\0';
	redir += 2;
	while (*redir == ' ')
		redir++;
	delim = ft_strdup(redir);
	end = delim + ft_strlen(delim) - 1;
	while (end > delim && (*end == ' ' || *end == '\n'))
		*end-- = '\0';
	if (pipe(pipefd) == -1)
		return (perror("pipe"), free(delim));
	buffer = malloc(8192);
	if (!buffer)
	{
		free (delim);
		close(pipefd[0]);
		close(pipefd[1]);
		return ;
	}
	buffer[0] = '\0';
	printf("heredoc> ");
	while (fgets(line, sizeof(line), stdin))
	{
		line[ft_strcspn(line, "\n")] = '\0';
		if (!ft_strcmp(line, delim))
			break ;
		ft_strcat(buffer, line);
		ft_strcat(buffer, "\n");
		printf("heredoc> ");
	}
	write(pipefd[1], buffer, ft_strlen(buffer));
	close(pipefd[1]);
	input->inputfd = pipefd[0];
	free(buffer);
	free(delim);
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
