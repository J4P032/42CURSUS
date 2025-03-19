/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:27:19 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/19 12:45:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_exit_anim2(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		game->win->sprite[13].img[i].img = mlx_xpm_file_to_image(game->win->mlx,
				game->win->sprite[13].bitmap[i], &game->win->sprite[13].width,
				&game->win->sprite[13].height);

		if (!game->win->sprite[13].img[i].img)
		{
			clean_up_memory(game);
			exit (1);
		}
		i++;
	}
}
void	load_exit(t_game *game)
{
	game->win->sprite[13].bitmap[0] = "./textures/cherry_00.xpm";
	game->win->sprite[13].bitmap[1] = "./textures/cherry_01.xpm";
	game->win->sprite[13].bitmap[2] = "./textures/cherry_02.xpm";
	game->win->sprite[13].width = 64;
	game->win->sprite[13].height = 64;
	load_exit_anim2(game);
}
