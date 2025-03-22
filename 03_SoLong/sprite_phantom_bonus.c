/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_phantom_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:28:39 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/22 14:34:14 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	load_phantom_sprite(t_game *g)
{
		g->win->sprite[14].img[0].img = mlx_xpm_file_to_image(g->win->mlx,
				g->win->sprite[14].bitmap[0], &g->win->sprite[14].width,
				&g->win->sprite[14].height);
		g->win->sprite[15].img[0].img = mlx_xpm_file_to_image(g->win->mlx,
			g->win->sprite[15].bitmap[0], &g->win->sprite[15].width,
			&g->win->sprite[15].height);
		if (!g->win->sprite[14].img[0].img || !g->win->sprite[15].img[0].img)
		{
			clean_up_memory(g);
			exit (1);
		}
}

void	load_phantom(t_game *game)
{
	game->win->sprite[14].bitmap[0] = "./textures/g_phantom_r_00.xpm";
	game->win->sprite[15].bitmap[0] = "./textures/g_phantom_l_00.xpm";
	game->win->sprite[14].width = 64;
	game->win->sprite[14].height = 64;
	game->win->sprite[15].width = 64;
	game->win->sprite[15].height = 64;
	load_phantom_sprite(game);
}
