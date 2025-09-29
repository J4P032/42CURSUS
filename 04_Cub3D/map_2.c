/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:46:31 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/24 15:18:53 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	free_and_get_line(int *is_first_char, char **line, int fd)
{
	free(*line);
	*line = get_next_line(fd);
	*is_first_char = 1;
	return (0);
}

void	init_textures(t_map *map)
{
	map->no_tex = NULL;
	map->ea_tex = NULL;
	map->we_tex = NULL;
	map->so_tex = NULL;
	map->floor_color = -1;
	map->sky_color = -1;
}

void	load_lines(int fd, char *line, t_map *map)
{
	size_t	i;

	i = 0;
	init_textures(map);
	line = jump_to_map(fd, line, map);
	map->columns = 0;
	while (line)
	{
		map->map[i] = line;
		if (map->columns < ft_strlen(map->map[i]))
			map->columns = ft_strlen(map->map[i]);
		i++;
		line = get_next_line(fd);
		if (!line && i < map->lines)
		{
			free_2d_array(map->map, i);
			map->map = NULL;
			return ;
		}
	}
	map->map[i] = NULL;
}

int	how_many_lines(char *map_dir)
{
	char	*line;
	int		cols;
	int		fd;

	cols = 0;
	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		return (write(1, "Error loading map\n", 18));
	line = get_next_line(fd);
	while (line != NULL)
	{
		cols++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (cols);
}

void	load_map(t_map *map, char *map_dir)
{
	char	*line;
	int		fd;

	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nError loading map\n");
		return ;
	}
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return ;
	}
	map->map = (char **)ft_calloc(how_many_lines(map_dir) + 1, sizeof(char *));
	if (!map->map)
	{
		free(line);
		close(fd);
		return ;
	}
	load_lines(fd, line, map);
	close(fd);
}
