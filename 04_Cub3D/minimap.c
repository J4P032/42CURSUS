/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:31:57 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/08 21:26:24 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	draw_minimap_frame(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAPSIZE)
	{
		x = 0;
		while (x < MINIMAPSIZE)
		{
			put_pixel(&game->win->canvas, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	draw_walls_around_player(t_game *game)
{
	int center;
	int	iposx;
	int	iposy;
	
	int	minix;
	int	miniy;
	int	i;
	int	j;
	
	iposx = (int)game->map->p_x;
	iposy = (int)game->map->p_y;

	center = (MINIMAPSIZE / 2) - (MINISPRITE / 2);
	
	miniy = center - iposy * MINISPRITE;
	j = miniy;
	minix = center - iposx * MINISPRITE;
	i = minix;
	while (miniy < MINIMAPSIZE)
	{
		minix = i;
		while (minix < MINIMAPSIZE)
		{
			if ((miniy - j) / MINISPRITE >= 0 && (miniy - j) / MINISPRITE < (int)game->map->lines
				&& (minix - i) / MINISPRITE >= 0 && (minix - i) / MINISPRITE < (int)game->map->columns
				&& game->map->map[(miniy - j) / MINISPRITE][(minix - i) / MINISPRITE] == '1')
			{				
				if (minix >= 0 && minix < MINIMAPSIZE
					&& miniy >= 0 && miniy < MINIMAPSIZE)
					draw_minisprite_on_canvas(game, game->win->sprite[4], minix, miniy);
			}
			minix += MINISPRITE;
		}
		miniy += MINISPRITE;
	}
}

void	draw_minimap(t_game *game)
{
	draw_minimap_frame(game);
	draw_walls_around_player(game);

}
