/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc_m.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:32:52 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/15 00:59:23 by mpico-bu         ###   ########.fr       */
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
	char	*cmd;

	*redir = '\0';
	redir += 2;
	while (*redir == ' ')
		redir++;
	delim = ft_strdup(redir);
	cmd = ft_strchr(delim, ' ');
	if (cmd)
	{
		*cmd = '\0';
		cmd++;
	}

	end = delim + ft_strlen(delim) - 1;
	while (end > delim && (*end == ' ' || *end == '\n'))
		*end-- = '\0';

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		free(delim);
		return;
	}

	buffer = malloc(8192);
	if (!buffer)
	{
		perror("malloc");
		free(delim);
		close(pipefd[0]);
		close(pipefd[1]);
		return;
	}
	buffer[0] = '\0';
	printf("heredoc> ");
	while (fgets(line, sizeof(line), stdin))
	{
		line[ft_strcspn(line, "\n")] = '\0';
		if (!ft_strcmp(line, delim))
			break;
		ft_strcat(buffer, line);
		ft_strcat(buffer, "\n");
		printf("heredoc> ");
	}
	if (buffer[0] == '\0')
		strcpy(buffer, "\n");
	write(pipefd[1], buffer, ft_strlen(buffer));
	close(pipefd[1]);
	input->inputfd = pipefd[0];
	if (cmd && *cmd)
	{
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork");
			close(pipefd[0]);
			free(buffer);
			free(delim);
			return;
		}
		if (pid == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			execlp("sh", "sh", "-c", cmd, NULL);
			perror("execlp");
			exit(1);
		}
		else
		{
			close(pipefd[0]);
			wait(NULL);
		}
	}
	free(buffer);
	free(delim);
}
