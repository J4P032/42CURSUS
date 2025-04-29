/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset_m.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:16:38 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/28 18:05:17 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	ft_search_env(int len, char *input, char ***envp, char **new_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], input, len) == 0 && (*envp)[i][len] == '=')
			free((*envp)[i]);
		else
			new_env[j++] = (*envp)[i];
		i++;
	}
}

void	ft_unset(char *input, char ***envp)
{
	int		i;
	int		len;
	char	**new_env;

	if (!input)
		return ;
	i = 0;
	len = ft_strlen(input);
	while ((*envp)[i])
		i++;
	new_env = ft_calloc(i, sizeof(char *));
	if (!new_env)
		return ;
	ft_search_env(len, input, envp, new_env);
	free(*envp);
	*envp = new_env;
}
