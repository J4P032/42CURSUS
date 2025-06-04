/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:26:18 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/30 10:45:46 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

bool	ft_manage_input_redirection(t_input *input, int i, bool lonely)
{
	char	*filename;

	if (lonely)
		filename = input->split_exp[i + 1];
	else
		filename = input->split_exp[i] + ft_strlen("<");
	if (input->inputfd > 2)
		close(input->inputfd);
	input->inputfd = open(filename, O_RDONLY);
	if (input->inputfd == -1)
	{
		input->last_exit_code = 1;
		ft_putstr_fd("miniyo: No such file or directory\n", 2);
		return (0);
	}
	update_input(input, i, lonely);
	return (1);
}

bool	ft_manage_output_redirection(t_input *input, int i, bool lonely)
{
	char	*filename;

	if (lonely)
		filename = input->split_exp[i + 1];
	else
		filename = input->split_exp[i] + ft_strlen(">");
	if (input->outputfd > 2)
		close(input->outputfd);
	input->outputfd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (input->outputfd == -1)
	{
		input->last_exit_code = 1;
		ft_putstr_fd("miniyo: Permission denied\n", 2);
		return (0);
	}
	update_input(input, i, lonely);
	return (1);
}

bool	ft_manage_append_redirection(t_input *input, int i, bool lonely)
{
	char	*filename;

	if (lonely)
		filename = input->split_exp[i + 1];
	else
		filename = input->split_exp[i] + ft_strlen(">>");
	if (input->outputfd > 2)
		close(input->outputfd);
	input->outputfd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (input->outputfd == -1)
	{
		input->last_exit_code = 1;
		ft_putstr_fd("miniyo: Permission denied\n", 2);
		return (0);
	}
	update_input(input, i, lonely);
	return (1);
}

static bool	ft_handle_heredoc_input(char *delimiter, int pipefd[2])
{
	struct sigaction	sa;
	struct sigaction	sa_old_int;
	struct sigaction	sa_old_quit;
	char				*line;

	heredoc_signals(&sa, &sa_old_int, &sa_old_quit);
	while (1)
	{
		if (g_signal_received)
		{
			restore_signals(&sa_old_int, &sa_old_quit);
			return (false);
		}
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break ;
		}
		print_heredoc(line, pipefd[1]);
	}
	return (restore_signals(&sa_old_int, &sa_old_quit), true);
}

bool	ft_manage_heredoc_redirection(t_input *input, int i, bool lonely)
{
	char	*delimiter;
	int		pipefd[2];

	if (lonely)
		delimiter = input->split_exp[i + 1];
	else
		delimiter = input->split_exp[i] + ft_strlen("<<");
	if (!delimiter)
		return (input->last_exit_code = 2, false);
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("miniyo: pipe error\n", 2);
		return (input->last_exit_code = 1, false);
	}
	if (!ft_handle_heredoc_input(delimiter, pipefd))
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (input->last_exit_code = 130, false);
	}
	close(pipefd[1]);
	if (input->inputfd > 2)
		close(input->inputfd);
	input->inputfd = pipefd[0];
	return (update_input(input, i, lonely), true);
}
