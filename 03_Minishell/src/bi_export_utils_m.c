/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:06:31 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/30 14:31:45 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	env_add(char ***envp, char *new_var)
{
	char	**new_env;
	int		i;

	new_env = ft_matrix_dup_plus(*envp, 1);
	if (!new_env)
		return ;
	i = 0;
	while (new_env[i])
		i++;
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	i = 0;
	while ((*envp)[i])
	{
		free((*envp)[i]);
		i++;
	}
	free(*envp);
	*envp = new_env;
}

static void	env_sort(char **env)
{
	int		i;
	int		swapped;
	char	*tmp;

	swapped = 1;
	while (swapped)
	{
		i = 0;
		swapped = 0;
		while (env[i] && env[i + 1])
		{
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i]) + 1) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

static void	env_declare(char *env)
{
	int		i;

	write(1, "declare -x ", 11);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		write(1, &env[i], 1);
		i++;
	}
	if (env[i] == '=')
	{
		write(1, "=\"", 2);
		write(1, &env[i + 1], ft_strlen(env + i + 1));
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

void	export_print_sorted(char **env)
{
	char	**copy;
	int		i;

	copy = ft_matrix_dup(env);
	if (!copy)
		return ;
	env_sort(copy);
	i = 0;
	while (copy[i])
	{
		env_declare(copy[i]);
		free(copy[i]);
		i++;
	}
	free(copy);
}

void	update_shlvl(char **arg)
{
	int		value;

	if (ft_strncmp(*arg, "SHLVL=", 6) == 0)
	{
		value = ft_atoi(*arg + 6);
		if (value < 0 || !ft_isdigit((*arg)[6]))
		{
			free(*arg);
			*arg = ft_strdup("SHLVL=0");
		}
	}
}
