/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:15:33 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/22 12:19:59 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	error_window(t_game *game, int option)
{
	if (option == 0)
		perror("Error creating window");
	else
		perror("Error creating canvas window");
	clean_up_memory(game);
	exit (1);
}

int	close_win(t_game *game)
{
	clean_up_memory(game);
	exit (0);
}

/*max screen size with xrandr in bash 3840x2160*/
/* void	check_size(t_game *game)
{
	size_t	columns;
	size_t	lines;
	size_t	max_columns;
	size_t	max_lines;

	columns = game->map->columns;
	lines = game->map->lines;
	max_columns = 3840 / SPRITE_WIDTH;
	max_lines = 2160 / SPRITE_HEIGHT;
	if (columns > max_columns || lines > max_lines)
	{
		write(1, "Error\n", 6);
		write(1, "Map too big for the screen\n", 27);
		clean_up_memory(game);
		exit (1);
	}
} */

void	draw_window(t_game *game)
{
	int	width;
	int	height;

	game->win->width = 1024; //game->map->columns * SPRITE_WIDTH;
	game->win->height = 768; //game->map->lines * SPRITE_HEIGHT;
	//check_size(game);
	width = game->win->width;
	height = game->win->height;
	if (!game->win->win)
	{
		game->win->win = mlx_new_window(game->win->mlx, width, height,
				"Cube3D");
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
	if (!game->win->canvas.addr)
		error_window(game, 1);
}
