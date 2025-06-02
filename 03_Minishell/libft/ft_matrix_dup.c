/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:01:07 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/28 17:05:19 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matrix_dup(char **matrix)
{
	int		i;
	char	**matrix2;

	i = 0;
	while (matrix && matrix[i])
		i++;
	matrix2 = malloc(sizeof(char *) * (i + 1));
	if (!matrix2)
		return (NULL);
	i = 0;
	while (matrix && matrix[i])
	{
		matrix2[i] = ft_strdup(matrix[i]);
		if (!matrix2[i])
		{
			while (--i >= 0)
				free(matrix2[i]);
			free(matrix2);
			return (NULL);
		}
		i++;
	}
	matrix2[i] = NULL;
	return (matrix2);
}

char	**ft_matrix_dup_plus(char **env, int extra)
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
