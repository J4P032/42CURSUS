/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_j.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:30:16 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/13 21:00:51 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_J_H
# define MINISHELL_J_H

# include <signal.h>
# include <stdio.h>

# define EPTY_NSP 0
# define EPTY_SP 1
# define SQUO_NSP 10
# define SQUO_SP 11
# define DQUO_NSP 20
# define DQUO_SP 21
# define D_Y_ODDCHAR "~%^=+}]:;/.,"
# define N_ODDCHAR "!@*-#`(){["

typedef struct s_pars
{
	char			*str;
	struct s_pars	*next;
}					t_pars;


typedef struct s_input
{
	char	*input;
	char	**input_split;
	char	**envp;
	t_pars	*parsed;
	int		*status;
	char	command[250];
	char	args[4096];
	size_t	word_after_command;
	size_t	word_after_arg;
	size_t	input_words;
	size_t	word;
	size_t	dollars;
	size_t	idollar;
	int		echo_error_n_arg;
	int		spaced;
	int		inputfd;
	int		outputfd;
	int		status_checked;
	pid_t	last_exit_code;
}			t_input;

//CHECK INPUT
void	compose_command_args(t_input *in);
void	compose_arg(t_input *in, size_t word);
void	parsing(t_input *in);

//BUILT INS
void	ft_echo(t_input *in);
void	manage_dollar(t_input *in, size_t w, int spaced);
int		valid_env(const char *str, t_input *in, size_t w);
void	ft_exit(t_input *in);
size_t	validlen_env(const char *str, char c);
size_t	invalidlen_env(const char *str);
void	print_rare_cases(t_input *in, size_t w, size_t *i);
void	print_rest_no_env(t_input *in, size_t w, size_t *i);

//SIGNALS
void	init_sigaction(struct sigaction *sa);

#endif
