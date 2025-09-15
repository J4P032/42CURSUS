/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-14 10:06:00 by user              #+#    #+#             */
/*   Updated: 2025-09-14 10:06:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	issafe(int x, int y, char **arr)
{
	if (x < 0 || y < 0)
		return (0);
	if (!arr[x])
		return (0);
	if (arr[x][y] == '\0' || arr[x][y] == ' ')
		return (0);
	return (1);
}

int	floodfill(int x, int y, char **arr)
{
	int	up;
	int	down;
	int	left;
	int	right;

	if (!issafe(x, y, arr))
		return (0);
	if (arr[x][y] == '1' || arr[x][y] == 'V')
		return (1);
	arr[x][y] = 'V';
	up = floodfill(x, y - 1, arr);
	down = floodfill(x, y + 1, arr);
	left = floodfill(x - 1, y, arr);
	right = floodfill(x + 1, y, arr);
	return (up && down && left && right);
}
int	check_map_errors(t_map *map)
{
	int	error;

	error = 0;
	if (map->NO_tex == NULL || map->NO_tex == NULL
		|| map->NO_tex == NULL || map->NO_tex == NULL
		|| map->floor_color == -1 || map->sky_color == -1)
		error = printf("Error\nNeed to specify textures and sky/floor color in .cub file\n");
	if (map->num_p != 1)
		error = printf("Error\nThere is no char start position, or more than one\n");
	if (map->no_valid_char)
		error = printf("Error\nThere is at least one invalid char in the map\n");
	if(error < 0)
		return (1);
	return (error);
}

void	zerify_map(t_map *map)
{
	size_t	j;
	size_t	i;

	j = 0;
	while (j < map->lines)
	{
		i = 0;
		while(map->map[j][i])
		{
			if (map->map[j][i] == ' ')
				map->map[j][i] = '0';
			i++;
		}
		j++;
	}
}