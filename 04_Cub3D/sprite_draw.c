/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:56:38 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/23 16:23:07 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_enemy_on_canvas(t_game *game, t_sprite sprite, int px, int py)
{
	int i;
	int j;
	int color;
	int tex_x;
	int tex_y;

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
					tex_x = (i * TEXTURE_W) / game->enemy.sprite_size;
					tex_y = (j * TEXTURE_H) / game->enemy.sprite_size;
					color = *(unsigned int *)(sprite.img[0].addr
						+ (tex_y * sprite.img[0].line_length
						+ tex_x * (sprite.img[0].bits_x_pixel / 8)));
					if (color != 0x0000FF00 && game->win->ray.hit_dist[px + i] > game->enemy.e_dist
                        && game->win->ray.green_pixel[px + i][py + j] == 1)
                       	put_pixel(&game->win->canvas, px + i, py + j, color);
                    else if (color != 0x0000FF00 && game->win->ray.door_dist[px + i] > game->enemy.e_dist)
                        put_pixel(&game->win->canvas, px + i, py + j, color);
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
			src = sprite.img[0].addr + (j * sprite.img[0].line_length
					+ i * (sprite.img[0].bits_x_pixel / 8));
			color = *(unsigned int *)src;
			put_pixel(&game->win->canvas, x + i, y + j, color);
			i++;
		}
		j++;
	}
}
