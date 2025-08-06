/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:05:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/06 17:18:58 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*modify the color with distance. More distance darker*/
/*LIGHT default is 2. Higher number brighter will be*/
void	modify_color_with_distance(t_game *game)
{
	float	factor;
	int		red;
	int		green;
	int		blue;

	if (game->win->ray.perp_wall_dist == 0)
		game->win->ray.perp_wall_dist = 1e-32;
	factor = LIGHT * 1.0f / (float)game->win->ray.perp_wall_dist;
	if (factor > 1.0f)
		factor = 1.0f;
	red = (int)(((game->win->ray.color >> 16) & 0xFF) * factor);
	green = (int)(((game->win->ray.color >> 8) & 0xFF) * factor);
	blue = (int)((game->win->ray.color & 0xFF) * factor);
	game->win->ray.color = (red << 16) | (green << 8) | blue;
}

void	color_picker(t_game *game)
{
	double	step;
	int		y;

	y = 0;
	step = TEXTURE_H / game->win->ray.line_height;
	game->win->sprite[game->win->ray.num_texture].y = y * step;
}

/*
Because all walls are '1' to know the side the hit has been produced (N-S-E-W)
we use 'side' and 'step_x/y.
side 0 && step_x 1 -> vertical walls, WEST side hit (ray goes left to right)
side 0 && step_x -1 -> vertical walls, EAST side hit (ray goes right to left)
side 1 && step_y 1 -> horizontal walls, NORTH side hit (ray goes up to down)
side 1 && step_y -1 -> horizontal walls, SOUTH side hit (ray goes down to up)

previous color set depending on
color format is hex. 0x[A][R][G][B] where in minilibx Alpha is not used
0x00FF0000 -> RED - WEST (3 texture index)
0x0000FF00 -> GREEN - NORTH (0)
0x000000FF -> BLUE - SOUTH (1)
0x00FFFF00 -> YELLOW - EAST (2)*/
void	choose_color(t_game *game)
{
	if (game->win->ray.side == 0)
	{
		if (game->win->ray.step_x == 1)
			game->win->ray.color = 0x00FF0000;
		else
			game->win->ray.color = 0x00FFFF00;
	}
	else
	{
		if (game->win->ray.step_y == 1)
			game->win->ray.color = 0x0000FF00;
		else
			game->win->ray.color = 0x000000FF;
	}
	color_picker(game);
	modify_color_with_distance(game);
}

/* void	choose_color(t_game *game)
{
	if (game->win->ray.side == 0)
	{
		if (game->win->ray.step_x == 1)
			game->win->ray.num_texture = 3;
		else
			game->win->ray.num_texture = 2;
	}
	else
	{
		if (game->win->ray.step_y == 1)
			game->win->ray.num_texture = 0;
		else
			game->win->ray.num_texture = 1;
	}
	color_picker(game);
	modify_color_with_distance(game);
} */

void	paint_ray(t_game *game, int x)
{
	int	y;

	y = game->win->ray.draw_start;
	while (y < game->win->ray.draw_end)
	{
		put_pixel(&game->win->canvas, x, y, game->win->ray.color);
		y++;
	}
}
