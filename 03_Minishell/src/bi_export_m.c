/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:06:31 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/26 20:18:35 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

bool	ft_check_variables(char *input)
{
	int		i;
	int		len;
	char	*equal;

	equal = ft_strchr(input, '=');
	if (!equal)
		return (1);
	len = equal - input;
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], input, len) == 0 && environ[i][len] == '=')
		{
			free (environ[i]);
			environ[i] = ft_strdup(input);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export(char *input)
{
	int		i;
	int		env_position;
	char	**new_env;

	if (ft_check_variables(input) == 1)
		return ;
	i = 0;
	env_position = 0;
	while (environ[env_position])
		env_position++;
	new_env = malloc(sizeof(char *) * (env_position + 2));
	if (!new_env)
		return ;
	while (i < env_position)
	{
		new_env[i] = ft_strdup(environ[i]);
		i++;
	}
	new_env[i++] = ft_strdup(input);
	new_env[i] = NULL;
	ft_matrix_free(environ);
	environ = new_env;
}
