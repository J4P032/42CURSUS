/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:29:35 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/22 19:05:06 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	load_sprites(t_game *game)
{
	draw_map(game);
	load_pacman(game);
	load_collect(game);
	load_exit(game);
	game->map_cpy = copy_map(game, game->map->map);
	load_phantom(game);
	if (!game->map_cpy)
	{
		clean_up_memory(game);
		exit (1);
	}
	game->win->sprite[0].j = game->map->p_x / SPRITE_WIDTH;
	game->win->sprite[0].i = game->map->p_y / SPRITE_HEIGHT;
}
