/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:49:36 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/12 21:54:49 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

/*Error numbers: */
/*-1 error reading map*/
/* 1 map not rectangle*/
void	check_line(char *line, char *next_line, t_map *map, int columns)
{
	size_t	i;

	i = 0;
	map->lines++;
	if (strlen(line) != columns)
		map->no_rectangle = 1;
	if (map->lines == 1 || next_line == NULL)
	{
		while(line[i])
		{
			if (line[i] == '1')
				map->num_walls++;
			i++;
		}
		return ;
	}
	while(line[i] && strlen(line) == columns)
	{
		if (line[0] == '1' || line[columns - 1] == '1')
			map->num_walls++;
		if (line[i] == 'C')
			map->num_c++;
		if (line[i] == 'P')
			map->num_p++;
		i++;
	}
}

void	check_map(t_map *map, char *map_dir)
{
	char	*line;
	char	*next_line;
	int		fd;
	int		columns;

	columns = 0;
	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		map->no_load = 1;
	next_line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		next_line = get_next_line(fd);
		if (map->lines == 0)
			columns = strlen(line);
		check_line(line, next_line, map, columns);
		free(line);
		line = next_line;
	}
	close (fd);
}

t_map	*process_map(char *map_dir, int *error)
{
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return ;
	check_map(map, map_dir);

	return (map);
}
