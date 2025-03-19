/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:04:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/19 22:22:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_sprites(t_game *game)
{
	draw_map(game);
	load_pacman(game);
	load_collect(game);
	load_exit(game);
	game->win->sprite[0].j = game->map->p_x / SPRITE_WIDTH;
	game->win->sprite[0].i = game->map->p_y / SPRITE_HEIGHT;
}
