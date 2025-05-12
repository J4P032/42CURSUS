/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc_m.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:32:52 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/11 23:33:19 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	handle_heredoc_redirection(t_input *input, char *redir)
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
