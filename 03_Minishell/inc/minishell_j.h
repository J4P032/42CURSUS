/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_j.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:30:16 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/04 18:17:15 by jrollon-         ###   ########.fr       */
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
# define SCP_EPTY_NSP 100
# define SCP_EPTY_SP 101
# define SCP_EPTY_2SP 102
# define SCP_QUO_NSP 110
# define SCP_QUO_SP 111
# define SCP_QUO_2SP 112

typedef struct s_input
{
	char	*input;
	char	**input_split;
	char	**envp;
	int		escaped;
	int		spaced;
	int		inputfd;
	int		outputfd;
	int		*status;	
}			t_input;

//BUILT INS
void	ft_echo(char **input, t_input *in);

void	init_sigaction(struct sigaction *sa);

#endif
