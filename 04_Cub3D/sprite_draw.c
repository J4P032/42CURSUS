/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:56:38 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/24 15:34:13 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	sprite_pixel_color(t_sprite sprite, int i, int j, int sprite_size)
{
	int	tex_x;
	int	tex_y;

	tex_x = (i * TEXTURE_W) / sprite_size;
	tex_y = (j * TEXTURE_H) / sprite_size;
	return (*(unsigned int *)(sprite.img[0].addr + (tex_y
			* sprite.img[0].line_length + tex_x
			* (sprite.img[0].bits_x_pixel / 8))));
}

static void	draw_enemy_pixel_if_visible(t_game *game, int x, int y, int color)
{
	if (color != 0x0000FF00
		&& game->win->ray.hit_dist[x] > game->enemy.e_dist
		&& game->win->ray.green_pixel[x][y] == 1)
		put_pixel(&game->win->canvas, x, y, color);
	else if (color != 0x0000FF00
		&& game->win->ray.door_dist[x] > game->enemy.e_dist)
		put_pixel(&game->win->canvas, x, y, color);
}

void	draw_enemy_on_canvas(t_game *game, t_sprite sprite, int px, int py)
{
	int	color;
	int	j;
	int	i;

	j = 0;
	while (j < game->enemy.sprite_size)
	{
		if (py + j >= 0 && py + j < WIN_H)
		{
			i = 0;
			while (i < game->enemy.sprite_size)
			{
				if (px + i >= 0 && px + i < WIN_W)
				{
					color = sprite_pixel_color(sprite, i, j,
							game->enemy.sprite_size);
					draw_enemy_pixel_if_visible(game, px + i, py + j, color);
				}
				i++;
			}
		}
		j++;
	}
}

void	draw_minisprite_on_canvas(t_game *game, t_sprite sprite, int x, int y)
{
	size_t	i;
	size_t	j;
	int		color;
	char	*src;

	j = 0;
	while (j < MINISPRITE)
	{
		i = 0;
		while (i < MINISPRITE)
		{
			src = sprite.img[0].addr + (j * sprite.img[0].line_length + i
					* (sprite.img[0].bits_x_pixel / 8));
			color = *(unsigned int *)src;
			put_pixel(&game->win->canvas, x + i, y + j, color);
			i++;
		}
		j++;
	}
}
