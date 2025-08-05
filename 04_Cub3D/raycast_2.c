/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:05:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/05 13:00:00 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*modify the color with distance. More distance darker*/
void	modify_color_with_distance(t_game *game)
{
	float	factor;
	int		red;
	int		green;
	int		blue;

	if (RAY.perp_wall_dist == 0)
		RAY.perp_wall_dist = 1e-32;
	factor = 2 * 1.0f / (float)RAY.perp_wall_dist;
	if (factor > 1.0f)
		factor = 1.0f;
	red = (int)(((RAY.color >> 16) & 0xFF) * factor);
	green = (int)(((RAY.color >> 8) & 0xFF) * factor);
	blue = (int)((RAY.color & 0xFF) * factor);
	RAY.color = (red << 16) | (green << 8) | blue;
}

/*
Because all walls are '1' to know the side the hit has been produced (N-S-E-W)
we use 'side' and 'step_x/y.
side 0 && step_x 1 -> vertical walls, WEST side hit (ray goes left to right)
side 0 && step_x -1 -> vertical walls, EAST side hit (ray goes right to left)
side 1 && step_y 1 -> horizontal walls, NORTH side hit (ray goes up to down)
side 1 && step_y -1 -> horizontal walls, SOUTH side hit (ray goes down to up)

color format is hex. 0x[A][R][G][B] where in minilibx Alpha is not used
0x00FF0000 -> RED - WEST
0x0000FF00 -> GREEN - NORTH
0x000000FF -> BLUE - SOUTH
0x00FFFF00 -> YELLOW - EAST*/
void	choose_color(t_game *game)
{
	if (RAY.side == 0)
	{
		if (RAY.step_x == 1)
		RAY.color = 0x00FF0000;
	else
		RAY.color = 0x00FFFF00;
	}
	else
	{
	if (RAY.step_y == 1)
		RAY.color = 0x0000FF00;
	else
		RAY.color = 0x000000FF;
	}
	modify_color_with_distance(game);
}
