/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:53:26 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/03 19:28:35 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

int	main(int argc, char **argv, char **envp)
{
	t_input				input;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	input.envp = ft_matrix_dup(envp);
	if (!input.envp)
		return (clean_all(&input), 1);
	init_sigaction(&sa);
	while (1)
	{
		input.input = readline("minishell$ ");
		if (!input.input)
			break ;
		if (input.input && *(input.input))
			ft_manage_history(input.input, 0);
		ft_manage_pipes(&input);
		free(input.input);
	}
	clean_all(&input);
	return (0);
}
