/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:19:28 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/08 14:58:15 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture_address(t_data *img, t_game *game)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_x_pixel,
		&img->line_length, &img->endian);
	if (!img->addr)
	{
		clean_up_memory(game, 0);
		exit (1);
	}
}

void	load_sprites(t_game *game)
{
	size_t		i;
	t_sprite	*sprite;
	
	i = 0;
	sprite = game->win->sprite;
	while (i < NUM_SPRITES)
	{
		sprite[i].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
				sprite[i].bitmap[0], &sprite[i].width, &sprite[i].height);
		if (!sprite[i].img[0].img)
		{
			clean_up_memory(game, 0);
			exit (1);
		}
		load_texture_address(&sprite[i].img[0], game);
		i++;
	}
}

void	load_sprites_and_background(t_game *game)
{
	t_sprite	*sprite;
	
	sprite = game->win->sprite;
	sprite[0].bitmap[0] = "./textures/NO_256.xpm";
	sprite[1].bitmap[0] = "./textures/SO_256.xpm";
	sprite[2].bitmap[0] = "./textures/EA_256.xpm";
	sprite[3].bitmap[0] = "./textures/WE_256.xpm";
	sprite[4].bitmap[0] = "./textures/miniwall.xpm";
	load_sprites(game);
	render_jumping_background(game);
}
