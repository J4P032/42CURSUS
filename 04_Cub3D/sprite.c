/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:19:28 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/05 15:50:34 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_walls(t_game *game)
{
	size_t	i;

	i = 0;
	SPRITE[0].bitmap[0] = "./textures/NO.xpm";
	SPRITE[1].bitmap[0] = "./textures/SO.xpm";
	SPRITE[2].bitmap[0] = "./textures/EA.xpm";
	SPRITE[3].bitmap[0] = "./textures/WE.xpm";
	SPRITE[0].width = 512;
	SPRITE[0].height = 512;
	//SPRITE[0].x = game->map->p_x;
	//SPRITE[0].y = game->map->p_y;
	while (i < 4)
	{
		SPRITE[i].img[0].img = mlx_xpm_file_to_image(game->win->mlx,
			SPRITE[i].bitmap[0], &SPRITE[i].width, &SPRITE[i].height);
		if (!SPRITE[i].img[0].img)
		{
			clean_up_memory(game);
			exit (1);
		}
		i++;
	}
}

void	load_sprites(t_game *game)
{
	//draw_map(game);
	load_walls(game);
	//SPRITE[0].j = game->map->p_x / TEXTURE_W;
	//SPRITE[0].i = game->map->p_y / TEXTURE_H;
}
