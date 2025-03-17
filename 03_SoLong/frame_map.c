/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:56:27 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/17 21:15:55 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_wall_to_canvas(t_game *game, size_t i, size_t j)
{
	int	x;
	int	y;

	x = SPRITE_WIDTH * j;
	y = SPRITE_HEIGHT * i;
	if (i == 0 && j == 0)
		draw_sprite_on_canvas(game, game->win->sprite[4], x, y);
	else if (i == 0 && j == game->map->columns - 1)
		draw_sprite_on_canvas(game, game->win->sprite[5], x, y);
	else if (i == game->map->lines - 1 && j == 0)
		draw_sprite_on_canvas(game, game->win->sprite[6], x, y);
	else if (i == game->map->lines - 1 && j == game->map->columns - 1)
		draw_sprite_on_canvas(game, game->win->sprite[7], x, y);
	else if (i == 0 && j > 0 && j < game->map->columns - 1)
		draw_sprite_on_canvas(game, game->win->sprite[8], x, y);
	else if (i == game->map->lines - 1 && j > 0 && j < game->map->columns - 1)
		draw_sprite_on_canvas(game, game->win->sprite[8], x, y);
	else if (j == 0 || j == game->map->columns - 1)
		draw_sprite_on_canvas(game, game->win->sprite[9], x, y);
	else
		draw_sprite_on_canvas(game, game->win->sprite[10], x, y);
}

void	frame_map(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < game->map->lines)
	{
		j = 0;
		while (j < game->map->columns)
		{
			if (game->map->map[i][j] == '1')
				draw_wall_to_canvas(game, i, j);
			j++;
		}
		i++;
	}
}
