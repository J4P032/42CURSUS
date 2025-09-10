/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:02:09 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/10 15:38:43 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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

void	check_internal_lines(char *line, t_map *map, size_t columns, size_t ln)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (i == 0 && line[0] == '1' && ft_strlen(line) == columns)
			map->num_walls++;
		if (i == (columns - 1) && line[columns - 1] == '1'
			&& ft_strlen(line) == columns)
			map->num_walls++;
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
		{
			map->num_p++;
			map->p_x = i + 0.5;
			map->p_y = (ln - 1) + 0.5;
			init_looking_direction(map, line[i]);
		}
		i++;
	}
}

void	check_line(char *line, char *next_line, t_map *map, size_t columns)
{
	size_t	i;

	i = 0;
	map->lines++;
	while (line[i])
	{
		if (!ft_strchr(VALID_MAP_CHARS, line[i]))
		{
			if (line[i] != ' ')
				map->no_valid_char = 1;
		}
		i++;
	}
	i = 0;
	if (map->lines == 1 || next_line == NULL)
	{
		while (line[i])
		{
			if (line[i] == '1')
				map->num_walls++;
			i++;
		}
		return ;
	}
	check_internal_lines(line, map, columns, map->lines);
}

void	check_map(t_map *map, char *map_dir)
{
	char	*line;
	char	*next_line;
	int		fd;

	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
	{
		write(1, "Error\n", 6);
		write(1, "Error loading map\n", 18);
		return ;
	}
	next_line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		next_line = get_next_line(fd);
		if (map->lines == 0)
			map->columns = ft_strlen(line);
		check_line(line, next_line, map, map->columns);
		free(line);
		line = next_line;
	}
	close(fd);
}

/*if we have an rectangled map surrounded by all walls, we have to have a...*/
/*...minimum of 2 top & botton lines all walls (2 * number of columns) ...*/
/*... plus each internal rows one wall in extremes (2 * (lines - 2))...*/
/*... -2 because we don't count again the top and botton lines. If we have...*/
/*...more or less than that because I didn't count the internal walls...*/
/*...then the map is not closed.*/
int	check_map_errors(t_map *map)
{
	int	error;

	error = 0;
	if (map->num_p != 1 || map->no_valid_char == 1)
		error = 1;
	if (map->num_p != 1)
		printf("Error\nThere is no char start position, or more than one\n");
	if (map->no_valid_char)
		printf("Error\nThere is at least one invalid char in the map\n");
	return (error);
}
// debug
//
//
void	print_2d_array(char **arr)
{
	int	x;
	int	y;

	x = 0;
	while (arr && arr[x]) // Recorrer filas hasta NULL
	{
		y = 0;
		while (arr[x][y] != '\0')
		{
			printf("%c", arr[x][y]);
			y++;
		}
		x++;
	}
}
//
//
//
/*map->lines == 0 in if, is because fd = -1 in open file*/
t_map	*process_map(char *map_dir)
{
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	check_map(map, map_dir);
	if (check_map_errors(map) || map->lines == 0)
		return (free(map), NULL);
	load_map(map, map_dir);
	if (!map->map)
		return (free(map), NULL);
	printf("FLOODFILL\n");
	if (!floodfill(map->p_y, map->p_x, map->map))
	{
		printf("Error\nMap not fully surrounded by walls\n");
		return (free(map), NULL);
	}
	printf("SALIMOS DE FLOODFILL\n");
	free_2d(map->map);
	load_map(map, map_dir);
	if (!map->map)
		return (free(map), NULL);
	print_2d_array(map->map);
	printf("MAPA CORRECTO, SALIMOS\n");
	return (map);
}
