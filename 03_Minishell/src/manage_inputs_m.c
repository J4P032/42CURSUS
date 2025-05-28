/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_inputs_m.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:28:00 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/27 14:32:01 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"


void	ft_manage_input(t_input *input)
{
	//input->inputfd = STDIN_FILENO;
	//input->outputfd = STDOUT_FILENO;
	//handle_redirection(input);
	if (ft_strcmp(input->command, "pwd") == 0)
		ft_pwd(input->args);
	else if (ft_strcmp(input->command, "cd") == 0)
		ft_cd(input);
	else if (ft_strcmp(input->command, "echo") == 0)
		echo_short(input, 1);
	else if (ft_strcmp(input->command, "export") == 0)
		ft_export(input, &input->envp);
	else if (ft_strcmp(input->command, "env") == 0)
		ft_env(input, input->envp);
	else if (ft_strcmp(input->command, "unset") == 0)//. unset sin mas lo que hace es poner una nueva linea de prompt
		ft_unset(input);
	else if (ft_strcmp(input->command, "exit") == 0)
		ft_exit(input);
	else
		execute_command(input);
	input->last_dollar_ = ft_last_str(input->split_exp);
	//input->last_exit_code = WEXITSTATUS(*input->status);
	//ft_input_free(input);
}
