/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:46:31 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/24 15:18:53 by marcoga2         ###   ########.fr       */
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

	map->dir_x = 0;
	map->dir_y = 0;
	map->plane_x = 0;
	map->plane_y = 0;
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

/*
** frees bidimensional array
*/
void	free_2d_array(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (i < size)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	blank_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	contains_invalid_char(char *str, char *valid)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	if (!str || blank_line(str))
		return (1);
	while (str[i] != '\0')
	{
		found = 0;
		j = 0;
		while (valid[j] != '\0')
		{
			if (str[i] == valid[j])
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (!found)
			return (1);
		i++;
	}
	return (0);
}
