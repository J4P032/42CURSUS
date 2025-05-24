/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_inputs_m.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:28:00 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/24 16:41:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"


void	ft_manage_input(t_input *input, int in_fd, int out_fd)
{
	input->inputfd = in_fd;
	input->outputfd = out_fd;
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
	ft_input_free(input);
}
