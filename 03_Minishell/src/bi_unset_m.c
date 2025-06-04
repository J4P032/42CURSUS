/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset_m.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:16:38 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/19 17:09:55 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

int	is_unset_var(char *env_entry, char **unset_vars)
{
	int	i;
	int	len;

	i = 0;
	while (unset_vars[i])
	{
		len = ft_strlen(unset_vars[i]);
		if (ft_strncmp(env_entry, unset_vars[i], len) == 0
			&& env_entry[len] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_search_env(char ***envp, char **unset_vars, char **new_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (is_unset_var((*envp)[i], unset_vars))
			free((*envp)[i]);
		else
			new_env[j++] = (*envp)[i];
		i++;
	}
}

void	ft_unset(t_input *input)
{
	int		i;
	char	**new_env;

	if (!input->split_exp)
		return ;
	i = 0;
	while (input->envp[i])
		i++;
	new_env = ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		return ;
	ft_search_env(&input->envp, input->split_exp, new_env);
	free(input->envp);
	input->envp = new_env;
}
