/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:46:31 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/10 16:06:44 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

/* plane_x/y is a rotation vector from dirx/y 90deg or π/2 so applying the...
...matrix rotation in 2D: 
R(a) = ⎡ cos(θ)     -sin(θ)⎤ * 	⎡x⎤ -> ⎡A B⎤ * ⎡E⎤ = ⎡AE + BF⎤
       ⎣ sin(θ)      cos(θ)⎦	⎣y⎦ -> ⎣C D⎦   ⎣F⎦   ⎣CE + DF⎦
so... 
	x' = x * cos(θ) + (y * -sin(θ))
	y' = x * sin(θ) + y * cos(θ)
as
	cos (π/2) = 0 // sin(π/2) = 1
ends
	x' = -y
	y' = x
We multiply by fov_factor to control the length of the plane vector,
which determines the field of view (FOV) width.*/
void	init_looking_direction(t_map *map, char c)
{
	double	fov_factor;

	fov_factor = tan((FOV * PI / 180.0) / 2);
	if (c == 'N')
		map->dir_y = -1;
	else if (c == 'S')
		map->dir_y = 1;
	else if (c == 'E')
		map->dir_x = 1;
	else if (c == 'W')
		map->dir_x = -1;
	map->plane_x = -map->dir_y * fov_factor;
	map->plane_y = map->dir_x * fov_factor;
}

// void	jump_to_map(int fd, char *line, t_map *map)
// {
// 	int i = 0;
// 	while (/**line contenga invalid chars*/)
// 	{
// 		if(line[i] == '\0')
// 		{
// 			i = 0;
// 			line = get_next_line(fd);
// 		}
// 		if (line[i] == 'N' && line[i + 1] == 'O')
// 		{
// 			//guardar textura norte!
// 		}
// 		if (line[i] == 'S' && line[i + 1] == 'O')
// 		{
// 			//guardar textura sur!
// 		}
// 		if (line[i] == 'W' && line[i + 1] == 'E')
// 		{
// 			//guardar textura oeste!
// 		}
// 		if (line[i] == 'E' && line[i + 1] == 'A')
// 		{
// 			//guardar textura este!
// 		}
// 		if (line[i] == 'F')
// 		{
// 			//guardar color suelo!
// 		}
// 		if (line[i] == 'C')
// 		{
// 			//guardar color cielo!
// 		}
// 		i++;
// 	}
// }

void	load_lines(int fd, char *line, t_map *map)
{
	size_t	i;

	i = 0;
	// jump_to_map(fd, line, map);
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
		printf("Error\nError loading map\n");
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
