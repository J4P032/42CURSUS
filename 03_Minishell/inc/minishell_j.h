/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_j.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:30:16 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/02 20:33:35 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_J_H
# define MINISHELL_J_H

# include <signal.h>

typedef struct	s_input
{
	char	*input;
	char	**input_split;
	char	**envp;
	int		is_spaced;
	int		*spaced;	
}			t_input;

//BUILT INS
void	ft_echo(char **input, t_input *in);

void	init_sigaction(struct sigaction *sa);

#endif
