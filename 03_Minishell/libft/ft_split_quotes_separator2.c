/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_separator2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:55:37 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/06 18:10:48 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../inc/minishell_j.h"

void	assign_token_status(t_input *input, t_split *sq, char letter)
{
	if (is_spaced(sq, sq->start))
	{
		if (sq->c == '"' || letter == '"')
			input->spaced = DQUO_SP;
		else if (sq->c == '\'' || letter == '\'')
			input->spaced = SQUO_SP;
		else if (sq->c == ' ' && (letter != '\'' || letter != '"'))
			input->spaced = EPTY_SP;
	}
	else
	{
		if (sq->c == '"' || letter == '"')
			input->spaced = DQUO_NSP;
		else if (sq->c == '\'' || letter == '\'')
			input->spaced = SQUO_NSP;
		else if (sq->c == ' ' && (letter != '\'' || letter != '"'))
			input->spaced = EPTY_NSP;
	}
}
