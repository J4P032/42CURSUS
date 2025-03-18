/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_collect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:28:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/18 14:46:57 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collect_sprite_anim(t_game *game, int x, int y)
{
	static int		i;
	static int		j;
	int				time;

	time = game->map->num_c;
	/* mlx_put_image_to_window(game->win->mlx, game->win->win,
		game->win->sprite[11].img[i].img, x, y); */
	draw_collect_on_canvas(game, x, y, i);
	j++;
	i = scale_time(&j, time);
}

void	frame_collect(t_game *game)
{
	size_t	i;
	size_t	j;
	int		x;
	int		y;

	i = 0;
	while (i < game->map->lines)
	{
		j = 0;
		while (j < game->map->columns)
		{
			if (game->map->map[i][j] == 'C')
			{
				x = SPRITE_WIDTH * j;
				y = SPRITE_HEIGHT * i;
				collect_sprite_anim(game, x, y);
			}
			j++;
		}
		i++;
	}
}
