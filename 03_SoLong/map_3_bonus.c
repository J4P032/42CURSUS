/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_3_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:49:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/25 12:03:29 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	restore_map(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (i < map->lines)
	{
		j = 0;
		while (j < map->columns)
		{
			if (map->map[i][j] == 'V')
				map->map[i][j] = '0';
			else if (map->map[i][j] == 'O')
				map->map[i][j] = 'C';
			else if (map->map[i][j] == 'H')
				map->map[i][j] = 'G';
			else if (map->map[i][j] == 'X')
				map->map[i][j] = 'E';
			else if (map->map[i][j] == 'J')
				map->map[i][j] = 'R';
			else if (map->map[i][j] == 'K')
				map->map[i][j] = 'B';
			j++;
		}
		i++;
	}
}

void	look_vertical(t_map *map, int i, int j)
{
	if (map->map[i - 1][j] == '0')
		map->map[i - 1][j] = 'v';
	else if (map->map[i - 1][j] == 'C')
		map->map[i - 1][j] = 'c';
	else if (map->map[i - 1][j] == 'E')
		map->map[i - 1][j] = 'e';
	else if (map->map[i - 1][j] == 'G')
		map->map[i - 1][j] = 'g';
	else if (map->map[i - 1][j] == 'R')
		map->map[i - 1][j] = 'r';
	else if (map->map[i - 1][j] == 'B')
		map->map[i - 1][j] = 'b';
	if (map->map[i + 1][j] == '0')
		map->map[i + 1][j] = 'v';
	else if (map->map[i + 1][j] == 'C')
		map->map[i + 1][j] = 'c';
	else if (map->map[i + 1][j] == 'E')
		map->map[i + 1][j] = 'e';
	else if (map->map[i + 1][j] == 'G')
		map->map[i + 1][j] = 'g';
	else if (map->map[i + 1][j] == 'R')
		map->map[i + 1][j] = 'r';
	else if (map->map[i + 1][j] == 'B')
		map->map[i + 1][j] = 'b';
}

void	look_horizontal(t_map *map, int *i, int *j)
{
	if (map->map[*i][(*j) + 1] == '0')
		map->map[*i][(*j) + 1] = 'v';
	else if (map->map[*i][(*j) + 1] == 'C')
		map->map[*i][(*j) + 1] = 'c';
	else if (map->map[*i][(*j) + 1] == 'E')
		map->map[*i][(*j) + 1] = 'e';
	else if (map->map[*i][(*j) + 1] == 'G')
		map->map[*i][(*j) + 1] = 'g';
	else if (map->map[*i][(*j) + 1] == 'R')
		map->map[*i][(*j) + 1] = 'r';
	if (map->map[*i][(*j) - 1] == '0')
		map->map[*i][(*j) - 1] = 'v';
	else if (map->map[*i][(*j) - 1] == 'C')
		map->map[*i][(*j) - 1] = 'c';
	else if (map->map[*i][(*j) - 1] == 'E')
		map->map[*i][(*j) - 1] = 'e';
	else if (map->map[*i][(*j) - 1] == 'G')
		map->map[*i][(*j) - 1] = 'g';
	else if (map->map[*i][(*j) - 1] == 'R')
		map->map[*i][(*j) - 1] = 'r';
	look_vertical(map, *i, *j);
	*i = 1;
	*j = -1;
}

/*to mark 'c' as visited we mark it 'O' (next letter of c-Ollectionable)*/
/*to mark 'e' as visited we mark it as 'X' (next letter of e-Xit)*/
/*to mark 'g' as visited we mark it as 'H' (next letter of g-Host)*/
void	search_visitable(t_map *map, int *i, int *j)
{
	if (map->map[*i][*j] == 'v')
		map->map[*i][*j] = 'V';
	else if (map->map[*i][*j] == 'c')
	{
		map->check_c++;
		map->map[*i][*j] = 'O';
	}
	else if (map->map[*i][*j] == 'e')
	{
		map->check_e++;
		map->map[*i][*j] = 'X';
	}
	else if (map->map[*i][*j] == 'g')
		map->map[*i][*j] = 'H';
	else if (map->map[*i][*j] == 'r')
		map->map[*i][*j] = 'J';
	else if (map->map[*i][*j] == 'b')
		map->map[*i][*j] = 'K';
	else if (map->map[*i][*j] == 'p')
		map->map[*i][*j] = 'P';
	if (map->map[*i][(*j) + 1] == 'B')
		map->map[*i][(*j) + 1] = 'b';
	else if (map->map[*i][(*j) - 1] == 'B')
		map->map[*i][(*j) - 1] = 'b';
	look_horizontal(map, i, j);
}

/*We start from player (P) position and rename it (p). Look horizontal and...*/
/*...vertical. If we find '0' I rename them to 'v' (visitable). If we find 'C'*/
/*...to 'c', 'E' to 'e', 'G' to 'g'. And we "visit" the first v,c,e,g marked.*/
/*...when moving if it is a 'c' or 'e' we count it and proceed to mark next.. */
/*...v,c,e,g's we find. If I don't find any new, I cycle-find the map to first*/
/*...v,c,e,g marked and start back from it, until we don't find anymore...*/
/*...then I compare the counter of 'c' and 'e' if are the same as stored.*/
/*...at the end we change the 'V's to '0'. 'O' to 'C'. 'X' to 'E' & 'H' to 'G'*/
int	check_map_solution(t_map *map)
{
	int	i;
	int	j;

	map->map[map->p_y / SPRITE_HEIGHT][map->p_x / SPRITE_WIDTH] = 'p';
	i = 1;
	while (i < (int)map->lines)
	{
		j = 0;
		while (j < (int)map->columns)
		{
			if (map->map[i][j] == 'p' || map->map[i][j] == 'v'
				|| map->map[i][j] == 'c' || map->map[i][j] == 'e'
				|| map->map[i][j] == 'g' || map->map[i][j] == 'r'
				|| map->map[i][j] == 'b')
				search_visitable(map, &i, &j);
			j++;
		}
		i++;
	}
	if (map->check_c == map->num_c && map->check_e == map->num_e)
	{
		restore_map(map);
		return (1);
	}
	return (0);
}
