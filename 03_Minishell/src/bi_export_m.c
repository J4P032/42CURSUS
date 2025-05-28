/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:06:31 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/26 19:05:23 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

char	**dup_env(char **env, int extra)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env && env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + extra + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	env_add(char ***envp, char *new_var)
{
	char	**new_env;
	int		i;

	new_env = dup_env(*envp, 1);
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

static char	**env_copy(char **env)
{
	char	**copy;
	int		i;

	i = 0;
	while (env[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
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

static void	print_declare(char *env)
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

	copy = env_copy(env);
	if (!copy)
		return ;
	env_sort(copy);
	i = 0;
	while (copy[i])
	{
		print_declare(copy[i]);
		free(copy[i]);
		i++;
	}
	free(copy);
}

static int	is_valid_key(char *str)
{
	int i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	// si empieza con '=' o es solo '='
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

static void	update_shlvl(char **arg)
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
		if (ft_strncmp(env[i], key, len) == 0 &&
			(env[i][len] == '=' || env[i][len] == '\0'))
		{
			free(env[i]);
			env[i] = ft_strdup(arg);
			free(key);
			return ;
		}
		i++;
	}
	env_add(envp, arg); // solo lo añade si no existe
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
		if (is_valid_key(input->split_exp[i]))
		{
			if (ft_strncmp(input->split_exp[i], "SHLVL=", 6) == 0)
				update_shlvl(&input->split_exp[i]);
			export_var(input->split_exp[i], envp);
		}
		else
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
	if (!input->split_exp[1])
		export_print_sorted(*envp);
	else
		export_args(input, envp);
}
