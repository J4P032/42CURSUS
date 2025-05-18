/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:53:26 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/18 16:43:09 by jrollon-         ###   ########.fr       */
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
		clean_all(&input, 1);
	init_sigaction(&sa);
	input.input_split = NULL;
	input.status = NULL;
	input.filename = NULL;
	input.parsed = NULL;
	while (1)
	{
		input.input = readline("\001\033[1;32m\002miniyo$\001\033[0m\002 ");
		if (!input.input)
			break ;
		if (!input.input[0])
		{
			free(input.input);
			continue ;
		}
		if (input.input && *(input.input))
			ft_manage_history(input.input, 0);
		input.input_split = ft_split_quotes(input.input, ' ', &input);
		if (!input.input_split || !input.input_split[0])
		{
			free(input.input);
			continue ;
		}
		compose_command_args(&input);\
		parsing(&input); //EN CONSTRUCCION
		compose_command_args(&input);//tiene que estar doble.
		/* printf("============\nPARSEADO:%s\n==========\n", input.parsed);
		printf("command:%s\n", input.command);//
		printf("arg:%s\n-------------\n", input.args);// */
		ft_manage_pipes(&input);
		free(input.input);
	}
	clean_all(&input, 0);
	return (0);
}
