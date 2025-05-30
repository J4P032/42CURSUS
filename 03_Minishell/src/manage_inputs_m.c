/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_inputs_m.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:28:00 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/30 01:28:27 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"


void	ft_manage_input(t_input *input)
{
	if (handle_redirection(input) == 1)
		return ;
	//printf("============\nPARSEADO:%s\n==========\n", input->parsed);
	
	/*
	printf("============\nPARSEADO:%s\n==========\n", input->parsed);
	printf("input:%s\n", input->input);
	printf("command:%s\n", input->command);
	printf("arg:%s\n", input->args);
	printf("parsed:%s\n", input->parsed);
	
	for (size_t i = 0; input->input_split[i]; i++)//
		ft_printf("Input split %d:%s %d\n", i, input->input_split[i], input->input_split[i]);//
	for (size_t i = 0; input->split_exp[i]; i++)//
		ft_printf("Split exp %d:%s %d\n", i, input->split_exp[i], input->status_exp[i]);//
	printf("-----SALIDA-----\n"); 
	*/
	//printf("parseado:%s\n", input->parsed);
	


	if (ft_strcmp(input->command, "") == 0 || input->command == NULL);
	else if (ft_strcmp(input->command, "pwd") == 0)
		ft_pwd(input->args);
	else if (ft_strcmp(input->command, "cd") == 0)
		ft_cd(input);
	else if (ft_strcmp(input->command, "echo") == 0)
		echo_short(input, input->outputfd);
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
	//ft_printf("Comand: %s\n", input->command);
	//ft_printf("last_exit_code_: %s\n", input->last_dollar_);
}
