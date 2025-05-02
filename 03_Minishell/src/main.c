/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:53:26 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/02 20:41:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	ft_manage_input(t_input *input, char ***envp)
{
	input->input_split = ft_split_quotes(input->input, ' ', input);
	if (!input->input_split || !input->input_split[0])
		return ;
	if (ft_strcmp(input->input_split[0], "pwd") == 0)
		ft_pwd(input->input_split);
	else if (ft_strcmp(input->input_split[0], "cd") == 0)
		ft_cd(input->input_split, *envp);
	else if (ft_strcmp(input->input_split[0], "echo") == 0)
		ft_echo(input->input_split, input);
	else if (ft_strcmp(input->input_split[0], "export") == 0
		&& input->input_split[1])
		ft_export(input->input_split[1], envp);
	else if (ft_strcmp(input->input_split[0], "env") == 0)
		ft_env(input->input_split, *envp);
	else if (ft_strcmp(input->input_split[0], "unset") == 0
		&& input->input_split[1])
		ft_unset(input->input_split[1], envp);
	else if (execute_command(input->input, 0, 0, *envp) == 1)
		return (ft_input_free(input));
	else 
		printf("%s: command not found\n", input->input_split[0]);
	ft_input_free(input);
}

int	main(int argc, char **argv, char **envp)
{
	t_input				input;
	struct sigaction	sa;
	char				**my_envp;

	(void)argc;
	(void)argv;
	input.envp = ft_matrix_dup(envp);
	if (!input.envp)
		return (clean_all(&input), 1);
	init_sigaction(&sa);
	while (1)
	{
		input.input = readline("minishell$ ");
		if(!input.input)
			break ;
		if	(input.input && *(input.input))
			ft_manage_history(input.input, 0);
		ft_manage_input(&input, &my_envp);
		free(input.input);
	}
	clean_all(&input);
	return (0);
}
