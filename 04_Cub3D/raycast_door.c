/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:39:04 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/08 15:08:52 by jrollon-         ###   ########.fr       */
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




void	door_color_picker(t_game *game, int y, int i)
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
		game->win->ray.colors[y] = search_color_in_door(
				&sprite[i].img[0], game->win->ray.tex_x, tex_y, game);
		y++;
	}
	if (y < WIN_H)
		game->win->ray.colors[y] = 0xFFFFFFFF;
}



void	paint_ray_door(t_game *game, int x)
{
	int	y;
	int	color;

	y = game->win->ray.draw_start;
	while (y < game->win->ray.draw_end)
	{
		color = game->win->ray.colors[y];
		if (color != 0x0000FF00)
			put_pixel(&game->win->canvas, x, y, color);
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

void	run_dda_door(t_game *game)
{
	t_ray	*ray;

	ray = &game->win->ray;
	while (ray->hit == 0)
	{
		if (ray->dist_x <= ray->dist_y)
		{
			ray->dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y >= 0 && ray->map_y < (int)game->map->lines
			&& ray->map_x >= 0 && ray->map_x < (int)game->map->columns
			&& game->map->map[ray->map_y][ray->map_x] == 'd')
			ray->hit = 1;
		else if (game->map->map[ray->map_y][ray->map_x] == '1')
			break;
	}
}

void	set_draw_length_without_fish_fx_door(t_game *game)
{
	t_ray	*ray;

	ray = &game->win->ray;
	if (ray->side == 0)
	{
		ray->perp_wall_dist = ray->dist_x - ray->delta_dist_x;
		ray->wallx = game->map->p_y + ray->perp_wall_dist * ray->dir_y;
	}
	else
	{
		ray->perp_wall_dist = ray->dist_y - ray->delta_dist_y;
		ray->wallx = game->map->p_x + ray->perp_wall_dist * ray->dir_x;
	}
	ray->wallx = ray->wallx - floor(ray->wallx);
	ray->line_height = (int)((WIN_H / ray->perp_wall_dist) * WALL_HEIGHT);
	ray->draw_start = (-ray->line_height / 2) + (WIN_H / 2)
		+ ray->walking_height;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (WIN_H / 2) + ray->walking_height;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

/*change index to make animation of it*/
int	add_index(t_game *game, int option)
{
	game->player.i++;
	if (game->player.i >= TIME_TO_ANIMATE && option == 1)
	{
		game->player.i = 0;
		if (game->player.index == 17)
			return (game->player.index);
		else
			return (game->player.index++);
	}
	if (game->player.index > 17 && option == 1)
		game->player.index = 17;
	if (game->player.i >= TIME_TO_ANIMATE && option == 0)
	{
		game->player.i = 0;
		if (game->player.index == 13)
			return (game->player.index);
		else
			return (game->player.index--);
	}
	if (game->player.index < 13 && option == 0)
		game->player.index = 13;
	return (game->player.index);
}

void	state_of_the_door(t_game *game, double py, double px)
{
	char	n_grid;
	char	s_grid;
	char	e_grid;
	char	w_grid;
	char	grid;
	
	n_grid = game->map->map[(int)floor(py) - 1][(int)floor(px)];
	s_grid = game->map->map[(int)floor(py) + 1][(int)floor(px)];
	e_grid = game->map->map[(int)floor(py)][(int)floor(px) + 1];
	w_grid = game->map->map[(int)floor(py)][(int)floor(px) - 1];
	grid = game->map->map[(int)floor(py)][(int)floor(px)];
	if (n_grid == 'd' || e_grid == 'd' || s_grid == 'd' || w_grid == 'd'
		|| grid == 'd')
		door_color_picker(game, game->win->ray.draw_start, add_index(game, 1));
	else
		door_color_picker(game, game->win->ray.draw_start, add_index(game, 0));
}

void	raycaster_door(t_game *game, int x)
{
	double	factor;
	t_ray	*ray;

	factor = 0;
	ray = &game->win->ray;
	if (game->player.moving)
		factor = 0.005;
	if (game->player.running && game->player.moving)
		factor = 0.01;
	ray->hit = 0;
	ray->hit_door = 0;
	ray->camera_x = 2 * x / (double)WIN_W - 1 + ray->walking_wave * factor;
	ray->dir_x = game->map->dir_x + game->map->plane_x * ray->camera_x;
	ray->dir_y = game->map->dir_y + game->map->plane_y * ray->camera_x;
	ray->map_x = (int)game->map->p_x;
	ray->map_y = (int)game->map->p_y;
	set_direction_of_ray_door(game);
	run_dda_door(game);
	if (game->win->ray.hit == 1)
	{
		set_draw_length_without_fish_fx_door(game);
		state_of_the_door(game, game->map->p_y, game->map->p_x);
		paint_ray_door(game, x);
	}
}
