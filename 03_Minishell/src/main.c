/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:53:26 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/01 21:28:50 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	ft_manage_input(char **input, char ***envp)
{
	if (!input || !input[0])
		return ;
	if (ft_strcmp(input[0], "pwd") == 0)
		ft_pwd(input);
	else if (ft_strcmp(input[0], "cd") == 0)
		ft_cd(input, *envp);
	else if (ft_strcmp(input[0], "echo") == 0)
		ft_echo(input);
	else if (ft_strcmp(input[0], "export") == 0 && input[1])
		ft_export(input[1], envp);
	else if (ft_strcmp(input[0], "env") == 0)
		ft_env(input, *envp);
	else if (ft_strcmp(input[0], "unset") == 0 && input[1])
		ft_unset(input[1], envp);
	else
		printf("%s: command not found\n", input[0]);
	ft_matrix_free(input);
}

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	struct sigaction	sa;
	char				**my_envp;

	(void)argc;
	(void)argv;
	my_envp = ft_matrix_dup(envp);
	if (!my_envp)
		return (clean_all(), 1);
	init_sigaction(&sa);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			ft_manage_history(input, 0);
		ft_manage_input(ft_split_quotes(input, ' '), &my_envp);
		free(input);
	}
	ft_matrix_free(my_envp);
	clean_all();
	return (0);
}
