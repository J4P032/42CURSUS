/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:26:18 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/29 23:26:04 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

bool ft_manage_input_redirection(t_input *input, int i, bool lonely)
{
    char *filename;

    if (lonely)
        filename = input->split_exp[i + 1];
    else
        filename = input->split_exp[i] + ft_strlen("<");
    if (input->inputfd > 2)
        close(input->inputfd);

    input->inputfd = open(filename, O_RDONLY);
    if (input->inputfd == -1)
	{
		input->last_exit_code = 1;
		ft_putstr_fd("miniyo: No such file or directory\n", 2);
		return (0);
	}
	update_input(input, i, lonely);
	return (1);
}

bool ft_manage_output_redirection(t_input *input, int i, bool lonely)
{
    char *filename;

    if (lonely)
        filename = input->split_exp[i + 1];
    else
        filename = input->split_exp[i] + ft_strlen(">");
    if (input->outputfd > 2)
        close(input->outputfd);

    input->outputfd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (input->outputfd == -1)
    {
        input->last_exit_code = 1;
        ft_putstr_fd("miniyo: Permission denied\n", 2);
        return (0);
    }
    update_input(input, i, lonely);
    return (1);
}

bool ft_manage_append_redirection(t_input *input, int i, bool lonely)
{
    char *filename;

    if (lonely)
        filename = input->split_exp[i + 1];
    else
        filename = input->split_exp[i] + ft_strlen(">>");
    if (input->outputfd > 2)
        close(input->outputfd);

    input->outputfd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (input->outputfd == -1)
    {
        input->last_exit_code = 1;
        ft_putstr_fd("miniyo: Permission denied\n", 2);
        return (0);
    }
    update_input(input, i, lonely);
    return (1);
}

bool ft_manage_redirection(t_input *input, char *search, int i, bool lonely)
{
	if (ft_strcmp(search, "<") == 0)
		if (ft_manage_input_redirection(input, i, lonely) == 0)
			return (0);
	if (ft_strcmp(search, ">") == 0)
		if (ft_manage_output_redirection(input, i, lonely) == 0)
			return (0);
	if (ft_strcmp(search, ">>") == 0)
		if (ft_manage_append_redirection(input, i, lonely) == 0)
			return (0);
	return (1);
}

int ft_check_one_redirection(t_input *input, int i, char *search)
{
	bool lonely;
	
	lonely = false;
	if (ft_strncmp(input->split_exp[i], search, ft_strlen(search)) == 0)
	{	
		if (ft_strcmp(input->split_exp[i], search) == 0)
			lonely = true;
		if (ft_manage_redirection(input, search, i, lonely) == 0)
			return (-1);
		return (1);
	}
	return (0);
}

bool handle_redirection(t_input *input)
{
	int i;
	int j;
	int result;
	char **redirections;
	
	i = 0;
	redirections = malloc(sizeof(char *) * 5);
	redirections[0] = ft_strdup("<<");
	redirections[1] = ft_strdup("<");
	redirections[2] = ft_strdup(">>");
	redirections[3] = ft_strdup(">");
	redirections[4] = NULL;

	//for (int j = 0; input->split_exp[j]; j++)
	//	printf("Split exp %d: %s\n", j, input->split_exp[j]);
	//printf("input: %s\n", input->input);
	//printf("command: %s\n", input->command);
	//printf("args: %s\n", input->args);
	//printf("inputfd: %d\n", input->inputfd);
	//printf("outputfd: %d\n", input->outputfd);

	while (input->split_exp[i])
	{
		j = 0;
		while (j < 4)
		{
			if (input->status_exp[i] != 0)	
			{
				j++;
				continue ;
			}
			result = ft_check_one_redirection(input, i, redirections[j]);
			if (result == 1)
			{
				i = 0;
				break ;
			}
			else if (result == -1)
				return (ft_matrix_free(&redirections), 1);
			j++;
		}
		i++;
	}

	ft_matrix_free(&redirections);
	return (0);
}
