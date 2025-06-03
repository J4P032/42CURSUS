/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_solve_j.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:28:12 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/03 12:28:44 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	heredoc_signals(struct sigaction *sa, struct sigaction *sa_old_int,
	struct sigaction *sa_old_quit)
{
	sigaction(SIGINT, NULL, sa_old_int);
	sigaction(SIGQUIT, NULL, sa_old_quit);
	sa->sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
	g_signal_received = 0;
}

void	restore_signals(struct sigaction *sa_old_int,
	struct sigaction *sa_old_quit)
{
	sigaction(SIGINT, sa_old_int, NULL);
	sigaction(SIGQUIT, sa_old_quit, NULL);
}

void	print_heredoc(char *line, int pipefd)
{
	write(pipefd, line, ft_strlen(line));
	write(pipefd, "\n", 1);
	free(line);
}
