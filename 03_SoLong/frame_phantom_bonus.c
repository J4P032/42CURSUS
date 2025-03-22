/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_phantom_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:49:08 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/22 20:37:39 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	phantom_sprite_anim(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->win->mlx, game->win->win, game->win->sprite[14].img[0].img, x, y);
}


void	phantom_anim(t_game *game)
{
	
	phantom_sprite_anim(game, game->win->sprite[14].x, game->win->sprite[14].y);
}	
