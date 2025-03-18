/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:43:00 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/18 11:34:43 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*get_mlx_addr(t_sprite *sprite)
{
	char	*aux;

	aux = mlx_get_data_addr(sprite->img[0].img, &sprite->img[0].bits_x_pixel,
			&sprite->img[0].line_length, &sprite->img[0].endian);
	return (aux);
}

void	load_corners(t_game *game)
{
	game->win->sprite[4].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
			game->win->sprite[4].bitmap[0], &game->win->sprite[4].width,
			&game->win->sprite[4].height);
	game->win->sprite[5].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
			game->win->sprite[5].bitmap[0], &game->win->sprite[5].width,
			&game->win->sprite[5].height);
	game->win->sprite[6].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
			game->win->sprite[6].bitmap[0], &game->win->sprite[6].width,
			&game->win->sprite[6].height);
	game->win->sprite[7].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
			game->win->sprite[7].bitmap[0], &game->win->sprite[7].width,
			&game->win->sprite[7].height);
	if (!game->win->sprite[6].img[0].img || !game->win->sprite[7].img[0].img
		|| !game->win->sprite[4].img[0].img
		|| !game->win->sprite[5].img[0].img)
	{
		clean_up_memory(game);
		exit (1);
	}
	game->win->sprite[4].img[0].addr = get_mlx_addr(&game->win->sprite[4]);
	game->win->sprite[5].img[0].addr = get_mlx_addr(&game->win->sprite[5]);
	game->win->sprite[6].img[0].addr = get_mlx_addr(&game->win->sprite[6]);
	game->win->sprite[7].img[0].addr = get_mlx_addr(&game->win->sprite[7]);
}

void	load_wall(t_game *game)
{
	game->win->sprite[8].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
			game->win->sprite[8].bitmap[0], &game->win->sprite[8].width,
			&game->win->sprite[8].height);
	game->win->sprite[9].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
			game->win->sprite[9].bitmap[0], &game->win->sprite[9].width,
			&game->win->sprite[9].height);
	game->win->sprite[10].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
			game->win->sprite[10].bitmap[0], &game->win->sprite[10].width,
			&game->win->sprite[10].height);
	if (!game->win->sprite[9].img[0].img || !game->win->sprite[8].img[0].img
		|| !game->win->sprite[10].img[0].img)
	{
		clean_up_memory(game);
		exit (1);
	}
	game->win->sprite[8].img[0].addr = get_mlx_addr(&game->win->sprite[8]);
	game->win->sprite[9].img[0].addr = get_mlx_addr(&game->win->sprite[9]);
	game->win->sprite[10].img[0].addr = get_mlx_addr(&game->win->sprite[10]);
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
	game->win->sprite[10].bitmap[0] = "./textures/wall_block.xpm";
	while (i < 11)
	{
		game->win->sprite[i].width = 64;
		game->win->sprite[i].height = 64;
		i++;
	}
	load_wall(game);
	load_corners(game);
	frame_map(game); //comentar esta linea si se quiere no redibujar por pixeles el mapa
}
