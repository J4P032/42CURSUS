/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:12:33 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/15 22:11:09 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_window(t_game *game, int option)
{
	if (option == 0)
		perror("Error creating window");
	else
		perror("Error creating canvas window");
	free (game->win);
	free (game->map);
	exit (1);
}

int	close_win(t_game *game)
{
	clean_up_memory(game);
	exit (0);
}

void	draw_window(t_game *game)
{
	int	width;
	int	height;

	game->win->width = game->map->columns * SPRITE_WIDTH;
	game->win->height = game->map->lines * SPRITE_HEIGHT;
	width = game->win->width;
	height = game->win->height;
	if (!game->win->win)
	{
		game->win->win = mlx_new_window(game->win->mlx, width, height, "SL");
		if (!game->win->win)
			error_window(game, 0);
	}
	game->win->canvas.img = mlx_new_image(game->win->mlx, width, height);
	if (!game->win->canvas.img)
		error_window(game, 1);
	game->win->canvas.addr = mlx_get_data_addr(game->win->canvas.img,
			&game->win->canvas.bits_x_pixel,
			&game->win->canvas.line_length,
			&game->win->canvas.endian);
}
