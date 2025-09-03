/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:30:52 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/03 15:21:50 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	check_wall_and_draw_it(t_game *game, int i, int j)
{
	t_map	*map;
	int		mapx;
	int		mapy;

	map = game->map;
	while (map->minix < MINIMAPSIZE)
	{
		mapx = (map->minix - i) / MINISPRITE;
		mapy = (map->miniy - j) / MINISPRITE;
		if (mapy >= 0 && mapy < (int)map->lines
			&& mapx >= 0 && mapx < (int)map->columns
			&& map->map[mapy][mapx] == '1')
		{
			if (map->minix >= 0 && map->minix < MINIMAPSIZE
				&& map->miniy >= 0 && map->miniy < MINIMAPSIZE)
				draw_minisprite_on_canvas(game, game->win->sprite[4],
					map->minix, map->miniy);
		}
		map->minix += MINISPRITE;
	}
}

void	draw_walls_around_player(t_game *game)
{
	int		i;
	int		j;
	t_map	*map;

	map = game->map;
	map->minicenter = (MINIMAPSIZE / 2) - (MINISPRITE / 2);
	map->miniy = map->minicenter - (int)(map->p_y) * MINISPRITE;
	j = map->miniy;
	map->minix = map->minicenter - (int)(map->p_x) * MINISPRITE;
	i = map->minix;
	while (map->miniy < MINIMAPSIZE)
	{
		map->minix = i;
		check_wall_and_draw_it(game, i, j);
		map->miniy += MINISPRITE;
	}
}

/*teta is the angle with North (0,1) is 0°*/
void	draw_player(t_game *game, t_sprite *sprite)
{
	int			teta;

	teta = (int)((180 * atan2(game->map->dir_y, game->map->dir_x) / PI) + 90);
	if (teta < 0)
		teta += 360;
	if (teta >= 337 || teta <= 23)
		*sprite = game->win->sprite[5];
	else if (teta > 23 && teta <= 68)
		*sprite = game->win->sprite[6];
	else if (teta > 68 && teta <= 113)
		*sprite = game->win->sprite[7];
	else if (teta > 113 && teta <= 157)
		*sprite = game->win->sprite[8];
	else if (teta > 157 && teta <= 203)
		*sprite = game->win->sprite[9];
	else if (teta > 203 && teta <= 247)
		*sprite = game->win->sprite[10];
	else if (teta > 247 && teta <= 293)
		*sprite = game->win->sprite[11];
	else if (teta > 293 && teta < 337)
		*sprite = game->win->sprite[12];
	draw_minisprite_on_canvas(game, *sprite, 70, 70);
}

void	draw_minimap(t_game *game)
{
	t_sprite	sprite;

	ft_memset(&sprite, 0, sizeof(sprite));
	draw_minimap_frame(game);
	draw_walls_around_player(game);
	draw_player(game, &sprite);
}
