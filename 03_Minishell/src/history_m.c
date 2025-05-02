/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:53:40 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/02 19:44:54 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	ft_manage_history(char *input, bool clean)
{
	static char	*last_input = NULL;

	if (clean)
	{
		if (last_input)
			free(last_input);
		return ;
	}
	if (!input[1] || !(*input))
		return ;
	if (!last_input || ft_strcmp(last_input, input) != 0)
	{
		add_history(input);
		if (last_input)
			free (last_input);
		last_input = ft_strdup(input);
	}
}
