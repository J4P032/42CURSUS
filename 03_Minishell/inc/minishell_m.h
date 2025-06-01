/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_m.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:51:03 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/30 14:41:43 by mpico-bu         ###   ########.fr       */
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
# include <sys/stat.h>
# include <errno.h>

void	ft_manage_history(char *input, bool clean);
void	clean_all(t_input *input, int error);

//BUILT INS
void	ft_pwd(char *args, t_input *input);
void	ft_env(t_input *in, char **envp);
void	ft_export(t_input *input, char ***envp);
void	ft_unset(t_input *input);
void	ft_cd(t_input *input);
bool	execute_command(t_input *input);
void	ft_manage_pipes(t_input *input);
bool	handle_redirection(t_input *input);
void	handle_heredoc_redirection(t_input *input, char *redir);
void	ft_manage_input(t_input *input);
void	init_input_struct(t_input *input);
void	update_input(t_input *input, int i, bool lonely);
void	ft_compose_parsed(t_input *input);
bool	ft_manage_input_redirection(t_input *input, int i, bool lonely);
bool	ft_manage_output_redirection(t_input *input, int i, bool lonely);
bool	ft_manage_append_redirection(t_input *input, int i, bool lonely);

void	export_print_sorted(char **env);
void	update_shlvl(char **arg);
void	env_add(char ***envp, char *new_var);

bool	ft_manage_heredoc_redirection(t_input *input, int i, bool lonely);

#endif
