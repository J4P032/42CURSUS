/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:53:26 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/27 14:20:14 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	init_input_struct(t_input *input)
{
	input->parsed = NULL;
	input->filename = NULL;
	input->input_split = NULL;
	input->split_exp = NULL;
	input->redir_in = NULL;
	input->redir_out = NULL;
	input->status = NULL;
	input->word_after_command = 0;
	input->word_after_arg = 0;
	input->input_words = 0;
	input->word = 0;
	input->dollars = 0;
	input->idollar = 0;
	input->env_len = 0;
	input->last_exit_code = 0;
	input->realloc_counter = 0;
	input->token = NULL;
	input->command = NULL;
	input->args = NULL;
	input->from_expand = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_input				input;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	
	input.envp = ft_matrix_dup(envp);
	if (!input.envp)
		clean_all(&input, 1);
	input.is_script = !isatty(STDIN_FILENO);
	init_sigaction(&sa);
	init_input_struct(&input);
	
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
		compose_command_args(&input);
		parsing(&input);
		/*
		 printf("============\nPARSEADO:%s\n==========\n", input.parsed);
		printf("command:%s\n", input.command);
		printf("arg:%s\n", input.args);
		for (size_t i = 0; input.split_exp[i]; i++)//
		ft_printf("%d.%s %d\n", i, input.split_exp[i], input.status_exp[i]);//
		printf("-----SALIDA-----\n"); 
		*/
		int i;
		bool pipe;
		pipe = false;
		i = 0;
		while (input.split_exp[i])
		{
			if (ft_strcmp(input.split_exp[i], "|") == 0 && input.status_exp[i] == 0)
			{
				ft_manage_pipes(&input);
				pipe = true;
				break ;
			}
			i++;	
		}
		if (!pipe)
		{
			ft_manage_input(&input);
		}
		free(input.input);
	}
	
	clean_all(&input, 0);
	if (input.is_script)
		exit(input.last_exit_code != 0 ? input.last_exit_code : 1);
	else
		exit(input.last_exit_code);
}
