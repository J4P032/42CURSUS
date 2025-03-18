/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:07:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/18 18:25:25 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_collect_death_anim(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		game->win->sprite[12].img[i].img = mlx_xpm_file_to_image(game->win->mlx,
				game->win->sprite[12].bitmap[i], &game->win->sprite[12].width,
				&game->win->sprite[12].height);
		if (!game->win->sprite[12].img[i].img)
		{
			clean_up_memory(game);
			exit (1);
		}
		i++;
	}
}

void	load_collect_anim(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		game->win->sprite[11].img[i].img = mlx_xpm_file_to_image(game->win->mlx,
				game->win->sprite[11].bitmap[i], &game->win->sprite[11].width,
				&game->win->sprite[11].height);
		if (!game->win->sprite[11].img[i].img)
		{
			clean_up_memory(game);
			exit (1);
		}
		game->win->sprite[11].img[i].addr = mlx_get_data_addr(
				game->win->sprite[11].img[i].img,
				&game->win->sprite[11].img[i].bits_x_pixel,
				&game->win->sprite[11].img[i].line_length,
				&game->win->sprite[11].img[i].endian);
		i++;
	}
}

void	load_collect(t_game *game)
{
	size_t	i;

	i = 11;
	game->win->sprite[11].bitmap[0] = "./textures/point_00.xpm";
	game->win->sprite[11].bitmap[1] = "./textures/point_01.xpm";
	game->win->sprite[11].bitmap[2] = "./textures/point_02.xpm";
	game->win->sprite[12].bitmap[0] = "./textures/pointdeath_00.xpm";
	game->win->sprite[12].bitmap[1] = "./textures/pointdeath_01.xpm";
	game->win->sprite[12].bitmap[2] = "./textures/pointdeath_02.xpm";
	while (i < 13)
	{
		game->win->sprite[i].width = 64;
		game->win->sprite[i].height = 64;
		i++;
	}
	load_collect_anim(game);
	load_collect_death_anim(game);
	//frame_collect(game);
}
