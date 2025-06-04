/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:53:26 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/29 17:49:20 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

static int	handle_input(t_input *input)
{
	input->input = readline("\001\033[1;32m\002miniyo$\001\033[0m\002 ");
	if (g_signal_received == SIGQUIT)
		clean_all(input, 131);
	else if (g_signal_received == SIGINT)
		input->last_exit_code = 130;
	g_signal_received = 0;
	if (!input->input)
		return (0);
	if (!input->input[0])
	{
		free(input->input);
		return (1);
	}
	ft_manage_history(input->input, 0);
	input->input_split = ft_split_quotes(input->input, ' ', input);
	if (!input->input_split || !input->input_split[0])
	{
		free(input->input);
		return (1);
	}
	return (2);
}

static void	retry_parse_command(t_input *input)
{
	free(input->filename);
	free(input->input);
	input->input = ft_strdup(input->parsed);
	free(input->parsed);
	ft_matrix_free(&input->input_split);
	input->input_split = ft_split_quotes(input->input, ' ', input);
	compose_command_args(input);
	parsing(input);
}

static void	shell_loop(t_input *input)
{
	int	status;

	while (1)
	{
		status = handle_input(input);
		if (status == 0)
			break ;
		else if (status == 1)
			continue ;
		compose_command_args(input);
		parsing(input);
		if ((!input->command || !input->command[0]) && input->parsed)
			retry_parse_command(input);
		ft_manage_pipes(input);
		free(input->input);
	}
}

bool	init_shlvl(t_input *input)
{
	char	*shlvl_str;
	int		shlvl_int;

	shlvl_str = get_env_value(input->envp, "SHLVL");
	if (!shlvl_str)
		return (1);
	shlvl_int = ft_atoi(shlvl_str);
	shlvl_str = NULL;
	shlvl_int += 1;
	shlvl_str = ft_itoa(shlvl_int);
	if (!shlvl_str)
		return (1);
	update_env(input, "SHLVL", shlvl_str);
	if (shlvl_str && shlvl_str[0])
		free(shlvl_str);
	shlvl_str = NULL;
	return (0);
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
	if (init_shlvl(&input))
		clean_all(&input, 1);
	input.is_script = !isatty(STDIN_FILENO);
	init_sigaction(&sa);
	init_input_struct(&input);
	shell_loop(&input);
	clean_all(&input, 0);
	if (input.is_script && input.last_exit_code != 0)
		exit(input.last_exit_code);
	else if (input.is_script && input.last_exit_code == 0)
		exit(1);
	else
		exit(input.last_exit_code);
}
