/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:04:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/11 13:49:50 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
void	draw_sprite(t_window *win)
{
	win->sprite.bitmap[0][0] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_r_00.xpm";
	win->sprite.bitmap[0][1] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_r_01.xpm";
	win->sprite.bitmap[0][2] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_r_02.xpm";
	win->sprite.width = 64;
	win->sprite.height = 64;
	win->sprite.x = WIDTH / 2;
	win->sprite.y = HEIGHT / 2;
	win->sprite.go_up = 0;
	win->sprite.go_right = 0;
	win->sprite.go_down = 0;
	win->sprite.go_left = 0;
	win->sprite.img.img = mlx_xpm_file_to_image(win->mlx, win->sprite.bitmap[0][0],
			&win->sprite.width, &win->sprite.width);
	if (!(win->sprite.img.img))
		return ;
/* 	win->sprite.img->addr = mlx_get_data_addr(win->sprite.img->img,
			&win->sprite.img->bits_x_pixel,
			&win->sprite.img->line_length,
			&win->sprite.img->endian); */
}
