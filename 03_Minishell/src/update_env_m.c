/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_m.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:49:50 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/29 22:55:37 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

static int	get_env_index(char **envp, char *key)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	*make_env_var(char *key, char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

static char	**copy_env(char **envp, int size)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * (size + 2));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i + 1] = NULL;
	return (new_envp);
}

void	update_env(t_input *input, char *key, char *value)
{
	int		index;
	char	*new_var;
	char	**new_envp;

	new_var = make_env_var(key, value);
	if (!new_var)
		return ;
	index = get_env_index(input->envp, key);
	if (index >= 0)
	{
		free(input->envp[index]);
		input->envp[index] = new_var;
	}
	else
	{
		index = 0;
		while (input->envp[index])
			index++;
		new_envp = copy_env(input->envp, index);
		if (!new_envp)
			return (free(new_var));
		new_envp[index] = new_var;
		free(input->envp);
		input->envp = new_envp;
	}
}
