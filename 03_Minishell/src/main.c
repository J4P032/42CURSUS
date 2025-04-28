/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:53:26 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/28 12:43:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	ft_manage_input(char **input)
{
	if (!input[0])
		return ;
	if (strcmp(input[0], "pwd") == 0)
		ft_pwd(input);
	else if (strcmp(input[0], "echo") == 0)
		ft_echo(input);
	else if (strcmp(input[0], "export") == 0 && input[1])
		ft_export(input[1]);
	else if (strcmp(input[0], "env") == 0)
		ft_env(input);
	else
		printf("%s: command not found\n", input[0]);
	ft_matrix_free(input);
}

int	main(void)
{
	char				*input;
	struct sigaction	sa;

	init_sigaction(&sa);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			ft_manage_history(input, 0);
		ft_manage_input(ft_split(input, ' '));
		free(input);
	}
	clean_all();
	return (0);
}
