/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_local_variable_m.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 03:46:38 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/21 03:48:43 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

bool is_variable_assignment(char *str)
{
    int i = 0;
    if (!str || !ft_isalpha(str[i]) && str[i] != '_')
        return (false);
    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
        i++;
    return str[i] == '=';
}

void set_local_variable(t_input *input, char *assignment)
{
	int		i;
	char	*key;
	size_t	key_len;

	if (!assignment)
		return ;
	key_len = 0;
	while (assignment[key_len] && assignment[key_len] != '=')
		key_len++;
	if (key_len == 0 || !assignment[key_len])
		return ;
	key = ft_substr(assignment, 0, key_len);
	if (!key)
		return ;
	i = 0;
	while (input->local_envp && input->local_envp[i])
	{
		if (ft_strncmp(input->local_envp[i], key, key_len) == 0 &&
			input->local_envp[i][key_len] == '=')
		{
			free(input->local_envp[i]);
			input->local_envp[i] = ft_strdup(assignment);
			free(key);
			return ;
		}
		i++;
	}
	input->local_envp = append_to_env(input->local_envp, assignment);
	free(key);
}
