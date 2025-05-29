/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_inputs_m.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:14:19 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/29 18:17:27 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void update_input_split_exp(t_input *input, int i, bool lonely)
{
	int j = 0;
	int k = 0;

	char **split_exp_dup = ft_matrix_dup(input->split_exp);
	ft_matrix_free(&input->split_exp);
	if (lonely)
		input->split_exp = malloc(sizeof(char *) * (ft_matrix_len(split_exp_dup) - 1));
	else
		input->split_exp = malloc(sizeof(char *) * (ft_matrix_len(split_exp_dup)));
	while (split_exp_dup[j])
	{
		if (j == i);
		else if (lonely && j == i + 1);
		else
		{
			input->split_exp[k]= ft_strdup(split_exp_dup[j]);
			k++;
		}
		j++;
	}
	input->split_exp[k] = NULL;
	ft_matrix_free(&split_exp_dup);
}

char	*ft_matrix_to_str(char **matrix)
{
	int		i;
	char	*result;
	char	*tmp;

	if (!matrix || !matrix[0])
		return (NULL);
	result = ft_strdup(matrix[0]);
	if (!result)
		return (NULL);
	i = 1;
	while (matrix[i])
	{
		tmp = ft_strjoin(result, " ");
		free(result);
		if (!tmp)
			return (NULL);
		result = ft_strjoin(tmp, matrix[i]);
		free(tmp);
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}

void update_input(t_input *input, int i, bool lonely)
{
	update_input_split_exp(input, i, lonely);
	free(input->input);
	input->input = ft_matrix_to_str(input->split_exp);
	ft_matrix_free(&input->input_split);
	input->input_split = ft_split_quotes(input->input, ' ', input);
	//free(input->args);
	compose_command_args(input);
	free(input->parsed);
	free(input->filename);
	for (int j = 0; input->split_exp[j] != 0 && j < 100; j++)
		input->status_exp[j] = 0;
	ft_matrix_free(&input->split_exp);
	parsing(input);
}