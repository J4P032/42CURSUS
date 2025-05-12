/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:06:31 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/11 20:51:22 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

bool	ft_manage_shlvl(char *input, char **envp, int i, int len)
{
	int	j;

	j = len + 1;
	free (envp[i]);
	while (input[j])
	{
		if (ft_isdigit(input[j++]))
			continue ;
		envp[i] = ft_strdup("SHLVL=0");
		return (1);
	}
	envp[i] = ft_strdup(input);
	return (1);
}

bool	ft_check_variables(char *input, char **envp)
{
	int		i;
	int		len;
	char	*equal;

	equal = ft_strchr(input, '=');
	if (!equal)
		return (1);
	len = equal - input;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], input, len) == 0 && envp[i][len] == '=')
		{
			if (ft_strncmp("SHLVL", input, len) == 0)
				return (ft_manage_shlvl(input, envp, i, len), 1);
			free (envp[i]);
			envp[i] = ft_strdup(input);
			if (!envp[i])
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export(char *input, char ***envp)
{
	int		i;
	int		env_position;
	char	**new_env;

	if (ft_check_variables(input, *envp) == 1)
		return ;
	i = 0;
	env_position = 0;
	while ((*envp)[env_position])
		env_position++;
	new_env = ft_calloc(env_position + 2, sizeof(char *));
	if (!new_env)
		return ;
	while (i < env_position)
	{
		new_env[i] = ft_strdup((*envp)[i]);
		if (!new_env[i++])
			return (ft_matrix_free(new_env));
	}
	new_env[i++] = ft_strdup(input);
	if (new_env[i])
		return (ft_matrix_free(new_env));
	ft_matrix_free(*envp);
	*envp = new_env;
}
