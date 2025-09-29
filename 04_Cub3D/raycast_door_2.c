/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_door_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:39:04 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/29 12:54:55 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	modify_color_with_distance_door(t_game *game, int color)
{
	int		factor;
	int		red;
	int		green;
	int		blue;

	if (game->win->ray.perp_wall_dist < 1e-6f)
		game->win->ray.perp_wall_dist = 1e-6f;
	factor = (int)(LIGHT / game->win->ray.perp_wall_dist * 256.0f);
	if (factor > 256)
		factor = 256;
	red = ((color >> 16) & 0xFF) * factor >> 8;
	green = ((color >> 8) & 0xFF) * factor >> 8;
	blue = (color & 0xFF) * factor >> 8;
	return ((red << 16) | (green << 8) | blue);
}

int	search_color_in_door(t_data *img, int x, int y, t_game *game)
{
	int	color;

	if (x < 0 || x > TEXTURE_W - 1 || y < 0 || y > TEXTURE_H - 1)
		return (0x00000000);
	if (!img || !img->addr)
		return (0x00000000);
	color = *(unsigned int *)(img->addr + y * img->line_length + x
			* (img->bits_x_pixel / 8));
	if (color != 0x0000FF00)
		color = modify_color_with_distance_door(game, color);
	return (color);
}

void	door_color_picker(t_game *game, int y, int i, int x)
{
	t_sprite	*sprite;
	double		scale;
	int			offset;
	int			tex_y;

	sprite = game->win->sprite;
	game->win->ray.tex_x = (int)(game->win->ray.wallx * TEXTURE_W);
	if ((game->win->ray.side == 0 && game->win->ray.step_x == -1)
		|| (game->win->ray.side == 1 && game->win->ray.step_y == 1))
		game->win->ray.tex_x = TEXTURE_W - game->win->ray.tex_x - 1;
	scale = (double)TEXTURE_H / (double)game->win->ray.line_height;
	while (y < game->win->ray.draw_end)
	{
		offset = y + (game->win->ray.line_height / 2)
			- (WIN_H / 2) - game->win->ray.walking_height;
		tex_y = (int)(offset * scale);
		game->win->ray.color = search_color_in_door(
				&sprite[i].img[0], game->win->ray.tex_x, tex_y, game);
		if (game->win->ray.color != 0x0000FF00)
		{
			put_pixel(&game->win->canvas, x, y, game->win->ray.color);
			game->win->ray.green_pixel[x][y] = 0;
		}
		y++;
	}
}

void	set_direction_of_ray_door(t_game *game)
{
	t_ray	*ray;

	ray = &game->win->ray;
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->dist_x = (game->map->p_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->dist_x = (ray->map_x + 1.0 - game->map->p_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->dist_y = (game->map->p_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->dist_y = (ray->map_y + 1.0 - game->map->p_y) * ray->delta_dist_y;
	}
}
