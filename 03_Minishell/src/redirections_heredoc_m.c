/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc_m.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 23:32:52 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/22 16:11:46 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

// ====== SEÑALES DE JAVI ======
volatile	sig_atomic_t heredoc_interrupted;

void heredoc_sigint_handler(int sig)
{
    (void)sig;
    heredoc_interrupted = 1;
}
// =============================

void	handle_heredoc_redirection(t_input *input, char *redir)
{
	char	*delim;
	char	*end;
	char	*buffer;
	char	line[1024];
	int		pipefd[2];
	char	*cmd;
	struct	sigaction sa; //señales javi
	struct sigaction sa_old_int;//señales javi
	struct sigaction sa_old_quit;//señales javi

	// ====== SEÑALES DE JAVI ======
	
	sigaction(SIGINT, NULL, &sa_old_int);
	sigaction(SIGQUIT, NULL, &sa_old_quit);

	sa.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	heredoc_interrupted = 0;
	
	// =============================
	
	*redir = '\0';
	redir += 2;
	while (*redir == ' ')
		redir++;
	delim = ft_strdup(redir);
	// ====== SEÑALES DE JAVI ======
	if (!delim)
	{
		sigaction(SIGINT, &sa_old_int, NULL);
		sigaction(SIGQUIT, &sa_old_quit, NULL);
		return ;
	}
	// =============================
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
		sigaction(SIGINT, &sa_old_int, NULL);//javi	signals
		sigaction(SIGQUIT, &sa_old_quit, NULL);//javi signals
		return ;
	}
	buffer = malloc(8192);
	if (!buffer)
	{
		perror("malloc");
		free(delim);
		close(pipefd[0]);
		close(pipefd[1]);
		sigaction(SIGINT, &sa_old_int, NULL);//javi signals
		sigaction(SIGQUIT, &sa_old_quit, NULL);//javi signals
		return ;
	}
	buffer[0] = '\0';
	printf("heredoc> ");
	while (fgets(line, sizeof(line), stdin))
	{
		
		// ====== SEÑALES DE JAVI ======
		if (heredoc_interrupted)
		{
			free(buffer);
			free(delim);
			close(pipefd[0]);
			close(pipefd[1]);
			sigaction(SIGINT, &sa_old_int, NULL);
			sigaction(SIGQUIT, &sa_old_quit, NULL);
			return ; //salimos por interrupcion de controlC
		}
		// =============================
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
			sigaction(SIGINT, &sa_old_int, NULL);//javi signals
			sigaction(SIGQUIT, &sa_old_quit, NULL);//javi signals
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
	sigaction(SIGINT, &sa_old_int, NULL);//javi signals
	sigaction(SIGQUIT, &sa_old_quit, NULL);//javi signals
}
