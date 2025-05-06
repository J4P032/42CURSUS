/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:53:26 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/06 19:04:41 by jrollon-         ###   ########.fr       */
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
		input.input = readline("\001\033[1;32m\002miniyo$\001\033[0m\002 ");
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
