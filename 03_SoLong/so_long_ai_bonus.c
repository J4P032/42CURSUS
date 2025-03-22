/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_ai_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:43:19 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/22 18:56:40 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	vacumm_map(char *map_copy, char *map)
{
	size_t	j;

	j = 0;
	while (map[j])
	{
		if (map[j] == 'C' || map[j] == 'P' || map[j] == 'E' || map[j] == 'G')
				map_copy[j] = '0';
		else
			map_copy[j] = map[j];
		j++;
	}
}

char **copy_map(t_game *game, char **map)
{
	char	**map_copy;
	size_t	i;
	size_t	j;
	
	i = 0;
	map_copy = (char **)ft_calloc(game->map->lines + 1, sizeof(char *));
	if (!map_copy)
		return (NULL);
	while (i < game->map->lines)
	{
		j = 0;
		map_copy[i] = (char *)ft_calloc(game->map->columns + 2, sizeof(char));
		if (!map_copy[i])
		{
			while (i > 0)
				free(map_copy[--i]);
			return (free (map_copy), NULL);
		}
		while (j++ < game->map->columns + 1)
			vacumm_map(map_copy[i], map[i]);
		i++;
	}
	return (map_copy);
}
