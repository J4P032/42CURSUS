/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_j.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:30:16 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/05 17:28:32 by jrollon-         ###   ########.fr       */
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

typedef struct s_input
{
	char	*input;
	char	**input_split;
	char	**envp;
	char	command[250];
	char	args[100];
	size_t	word_after_command;
	size_t	word_after_arg;
	size_t	input_words;
	int		spaced;
	int		inputfd;
	int		outputfd;
	int		*status;	
}			t_input;

//BUILT INS
void	ft_echo(t_input *in);

void	init_sigaction(struct sigaction *sa);

#endif
