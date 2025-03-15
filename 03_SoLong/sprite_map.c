/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:43:00 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/15 20:14:31 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_corners(t_game *game)
{
	game->win->sprite[4].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
				game->win->sprite[4].bitmap[0], &game->win->sprite[4].width,
				&game->win->sprite[4].height);
	game->win->sprite[5].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
				game->win->sprite[5].bitmap[0], &game->win->sprite[5].width,
				&game->win->sprite[5].height);
	if (!game->win->sprite[4].img[0].img || !game->win->sprite[5].img[0].img)
	{
		clean_up_memory(game);
		exit (1);
	}
	game->win->sprite[6].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
				game->win->sprite[6].bitmap[0], &game->win->sprite[6].width,
				&game->win->sprite[6].height);
	game->win->sprite[7].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
				game->win->sprite[7].bitmap[0], &game->win->sprite[7].width,
				&game->win->sprite[7].height);
	if (!game->win->sprite[6].img[0].img || !game->win->sprite[7].img[0].img)
	{
		clean_up_memory(game);
		exit (1);
	}
}

void	draw_wall(t_game *game)
{
	game->win->sprite[8].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
				game->win->sprite[8].bitmap[0], &game->win->sprite[8].width,
				&game->win->sprite[8].height);
	if (!game->win->sprite[8].img[0].img)
	{
		clean_up_memory(game);
		exit (1);
	}
	game->win->sprite[9].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
				game->win->sprite[9].bitmap[0], &game->win->sprite[9].width,
				&game->win->sprite[9].height);
	if (!game->win->sprite[9].img[0].img)
	{
		clean_up_memory(game);
		exit (1);
	}
}

void	draw_map(t_game *game)
{
	size_t	i;

	i = 4;
	game->win->sprite[4].bitmap[0] = "./textures/wall_00.xpm";
	game->win->sprite[5].bitmap[0] = "./textures/wall_01.xpm";
	game->win->sprite[6].bitmap[0] = "./textures/wall_10.xpm";
	game->win->sprite[7].bitmap[0] = "./textures/wall_11.xpm";
	game->win->sprite[8].bitmap[0] = "./textures/wall_horizontal.xpm";
	game->win->sprite[9].bitmap[0] = "./textures/wall_vertical.xpm";
	while (i < 10)
	{
		game->win->sprite[i].width = 64;
		game->win->sprite[i].height = 64;
		i++;
	}
	draw_wall(game);
	draw_corners(game);
}
