/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_m.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:51:03 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/16 12:55:54 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_M_H
# define MINISHELL_M_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

void	ft_manage_history(char *input, bool clean);
void	clean_all(t_input *input, int error);

//BUILT INS
void	ft_pwd(char *input);
void	ft_env(t_input *in, char **envp);
void	ft_export(char *input, char ***envp);
void	ft_unset(char *input, char ***envp);
bool	ft_cd(char **args, char **envp);

bool	execute_command(t_input *input);
void	ft_manage_pipes(t_input *input);
bool	handle_redirection(t_input *input);
void	handle_heredoc_redirection(t_input *input, char *redir);

#endif
