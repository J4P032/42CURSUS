/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_m.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:51:03 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/21 04:04:15 by mpico-bu         ###   ########.fr       */
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
void	ft_export(t_input *input_data, char ***envp);
void	ft_unset(t_input *input);
bool	ft_cd(t_input *input);

bool	execute_command(t_input *input);
void	ft_manage_pipes(t_input *input);
void	handle_redirection(t_input *input);
void	handle_heredoc_redirection(t_input *input, char *redir);
void	ft_manage_input(t_input *input, int in_fd, int out_fd);
void	set_local_variable(t_input *input, char *assignment);

#endif
