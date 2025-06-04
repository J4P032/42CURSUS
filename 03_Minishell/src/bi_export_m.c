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

static int	is_valid_key(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (!str[i])
		return (-1);
	if (str[0] == '=' || str[0] == '\0')
		return (0);
	return (1);
}

static char	*get_env_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static void	export_var(char *arg, char ***envp)
{
	char	**env;
	char	*key;
	int		i;
	int		len;

	key = get_env_key(arg);
	if (!key)
		return ;
	env = *envp;
	i = 0;
	len = ft_strlen(key);
	while (env && env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0
			&& (env[i][len] == '=' || env[i][len] == '\0'))
		{
			free(env[i]);
			env[i] = ft_strdup(arg);
			free(key);
			return ;
		}
		i++;
	}
	env_add(envp, arg);
	free(key);
}

static void	export_args(t_input *input, char ***envp)
{
	int		i;
	int		error_flag;

	i = 1;
	error_flag = 0;
	while (input->split_exp[i])
	{
		if (is_valid_key(input->split_exp[i]) == 1)
		{
			if (ft_strncmp(input->split_exp[i], "SHLVL=", 6) == 0)
				update_shlvl(&input->split_exp[i]);
			export_var(input->split_exp[i], envp);
		}
		else if (is_valid_key(input->split_exp[i]) == 0)
		{
			ft_putstr_fd("export: not a valid identifier\n", 2);
			error_flag = 1;
		}
		i++;
	}
	input->last_exit_code = error_flag;
}

void	ft_export(t_input *input, char ***envp)
{
	input->last_exit_code = 0;
	if (!input->split_exp[1] || !input->split_exp[1][0])
		export_print_sorted(*envp);
	else
		export_args(input, envp);
}
