/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_pacman.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:41:55 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/15 21:59:36 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_pacman_anim_vertical(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		game->win->sprite[2].img[i].img = mlx_xpm_file_to_image(game->win->mlx,
				game->win->sprite[2].bitmap[i], &game->win->sprite[2].width,
				&game->win->sprite[2].height);
		if (!game->win->sprite[2].img[i].img)
		{
			clean_up_memory(game);
			exit (1);
		}
		game->win->sprite[3].img[i].img = mlx_xpm_file_to_image(game->win->mlx,
				game->win->sprite[3].bitmap[i], &game->win->sprite[3].width,
				&game->win->sprite[3].height);
		if (!game->win->sprite[3].img[i].img)
		{
			clean_up_memory(game);
			exit (1);
		}
		i++;
	}
}

void	load_pacman_anim_horizontal(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		game->win->sprite[0].img[i].img = mlx_xpm_file_to_image(game->win->mlx,
				game->win->sprite[0].bitmap[i], &game->win->sprite[0].width,
				&game->win->sprite[0].height);
		if (!game->win->sprite[0].img[i].img)
		{
			clean_up_memory(game);
			exit (1);
		}
		game->win->sprite[1].img[i].img = mlx_xpm_file_to_image(game->win->mlx,
				game->win->sprite[1].bitmap[i], &game->win->sprite[1].width,
				&game->win->sprite[1].height);
		if (!game->win->sprite[1].img[i].img)
		{
			clean_up_memory(game);
			exit (1);
		}

		i++;
	}
}

void	load_pacman(t_game *game)
{
	int	width;
	int height;

	width = game->win->width;
	height = game->win->height;
	game->win->sprite[0].bitmap[0] = "./textures/pacman_r_00.xpm";
	game->win->sprite[0].bitmap[1] = "./textures/pacman_r_01.xpm";
	game->win->sprite[0].bitmap[2] = "./textures/pacman_r_02.xpm";
	game->win->sprite[1].bitmap[0] = "./textures/pacman_l_00.xpm";
	game->win->sprite[1].bitmap[1] = "./textures/pacman_l_01.xpm";
	game->win->sprite[1].bitmap[2] = "./textures/pacman_l_02.xpm";
	game->win->sprite[2].bitmap[0] = "./textures/pacman_u_00.xpm";
	game->win->sprite[2].bitmap[1] = "./textures/pacman_u_01.xpm";
	game->win->sprite[2].bitmap[2] = "./textures/pacman_u_02.xpm";
	game->win->sprite[3].bitmap[0] = "./textures/pacman_d_00.xpm";
	game->win->sprite[3].bitmap[1] = "./textures/pacman_d_01.xpm";
	game->win->sprite[3].bitmap[2] = "./textures/pacman_d_02.xpm";
	game->win->sprite[0].width = 64;
	game->win->sprite[0].height = 64;
	game->win->sprite[0].x = (width / 2) - game->win->sprite[0].width / 2;
	game->win->sprite[0].y = (height / 2) - game->win->sprite[0].height / 2;
	load_pacman_anim_horizontal(game);
	load_pacman_anim_vertical(game);
}
