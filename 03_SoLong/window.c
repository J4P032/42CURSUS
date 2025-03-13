/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:12:33 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/13 18:20:39 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_win(t_game *game)
{
	clean_up_memory(game);
	exit (0);
}

void	draw_window(t_game *game)
{
	if (!game->win->win)
	{
		game->win->win = mlx_new_window(game->win->mlx, WIDTH, HEIGHT, "SL");
		if (!game->win->win)
		{
			perror("Error creating window");
			free (game->win);
			free (game->map);
			exit (1);
		}
	}
	game->win->canvas.img = mlx_new_image(game->win->mlx, WIDTH, HEIGHT);
	if (!game->win->canvas.img)
	{
		perror("Error creating canvas window");
		free (game->win);
		free (game->map);
		exit (1);
	}
	game->win->canvas.addr = mlx_get_data_addr(game->win->canvas.img,
			&game->win->canvas.bits_x_pixel,
			&game->win->canvas.line_length,
			&game->win->canvas.endian);
}
