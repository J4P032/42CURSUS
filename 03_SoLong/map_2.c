/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:46:31 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/17 21:20:21 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

void	load_lines(int fd, char *line, t_map *map)
{
	size_t	i;

	i = 0;
	while (line)
	{
		map->map[i] = line;
		i++;
		line = get_next_line(fd);
		if (!line && i < map->lines)
		{
			while (i > 0)
			{
				i--;
				free(map->map[i]);
				map->map[i] = NULL;
			}
			free(map->map);
			map->map = NULL;
			return ;
		}
	}
	map->map[i] = NULL;
}

void	load_map(t_map *map, char *map_dir)
{
	char	*line;
	int		fd;

	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
	{
		write(1, "Error\n", 6);
		write(1, "Error loading map\n", 18);
		return ;
	}
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return ;
	}
	map->map = (char **)ft_calloc(map->lines + 1, sizeof(char *));
	if (!map->map)
	{
		free(line);
		close(fd);
		return ;
	}
	load_lines(fd, line, map);
	close (fd);
}
