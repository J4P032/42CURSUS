/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:23:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/16 15:42:16 by jrollon-         ###   ########.fr       */
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

/*-5 because we have loaded the previous 5 ones in load_sprites not animated*/
void	load_animated(t_game *game)
{
	size_t		i;
	size_t		j;
	t_sprite	*sprite;

	i = NUM_SPRITES - 1;
	sprite = game->win->sprite;
	while (i < (NUM_SPRITES - 5))
	{
		j = 0;
		while (j < SPRITES_ANIM)
		{
			sprite[i].img[j].img = mlx_xpm_file_to_image(game->win->mlx,
					sprite[i].bitmap[j], &sprite[i].width, &sprite[i].height);
			if (!sprite[i].img[j].img)
			{
				clean_up_memory(game, 0);
				exit (1);
			}
			load_texture_address(&sprite[i].img[j], game);
			j++;
		}
		i++;
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
	game->player.index = 14;
	game->enemy.float_index = 0;
	//load_animated(game);
}

void	load_sprites_and_background(t_game *game)
{
	t_sprite	*sprite;

	sprite = game->win->sprite;
	sprite[0].bitmap[0] = "./textures/stonewall.xpm";
	sprite[1].bitmap[0] = "./textures/stonewall.xpm";
	sprite[2].bitmap[0] = "./textures/stonewall_dark.xpm";
	sprite[3].bitmap[0] = "./textures/stonewall_dark.xpm";
	sprite[4].bitmap[0] = "./textures/miniwall.xpm";
	sprite[5].bitmap[0] = "./textures/MiniPlayer_N.xpm";
	sprite[6].bitmap[0] = "./textures/MiniPlayer_NE.xpm";
	sprite[7].bitmap[0] = "./textures/MiniPlayer_E.xpm";
	sprite[8].bitmap[0] = "./textures/MiniPlayer_SE.xpm";
	sprite[9].bitmap[0] = "./textures/MiniPlayer_S.xpm";
	sprite[10].bitmap[0] = "./textures/MiniPlayer_SW.xpm";
	sprite[11].bitmap[0] = "./textures/MiniPlayer_W.xpm";
	sprite[12].bitmap[0] = "./textures/MiniPlayer_NW.xpm";
	sprite[13].bitmap[0] = "./textures/door.xpm";
	sprite[14].bitmap[0] = "./textures/door_1.xpm";
	sprite[15].bitmap[0] = "./textures/door_2.xpm";
	sprite[16].bitmap[0] = "./textures/door_3.xpm";
	sprite[17].bitmap[0] = "./textures/door_4.xpm";
	sprite[18].bitmap[0] = "./textures/EA_256.xpm"; //enemigo
	load_sprites(game);
	render_jumping_background(game);
}
