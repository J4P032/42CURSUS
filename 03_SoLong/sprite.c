/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:04:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/11 15:04:54 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
void	draw_sprite(t_window *win)
{
	size_t	i;

	i = 0;
	win->sprite[0].bitmap[0] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_r_00.xpm";
	win->sprite[0].bitmap[1] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_r_01.xpm";
	win->sprite[0].bitmap[2] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_r_02.xpm";
	win->sprite[1].bitmap[0] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_l_00.xpm";
	win->sprite[1].bitmap[1] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_l_01.xpm";
	win->sprite[1].bitmap[2] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_l_02.xpm";
	win->sprite[0].width = 64;
	win->sprite[0].height = 64;
	win->sprite[0].x = WIDTH / 2;
	win->sprite[0].y = HEIGHT / 2;
	win->sprite[0].go_up = 0;
	win->sprite[0].go_right = 0;
	win->sprite[0].go_down = 0;
	win->sprite[0].go_left = 0;

	win->sprite[1].width = 64;
	win->sprite[1].height = 64;
	win->sprite[1].x = WIDTH / 2;
	win->sprite[1].y = HEIGHT / 2;
	win->sprite[1].go_up = 0;
	win->sprite[1].go_right = 0;
	win->sprite[1].go_down = 0;
	win->sprite[1].go_left = 0;
	while (i < 3)
	{
		win->sprite[0].img[i].img = mlx_xpm_file_to_image(win->mlx, win->sprite[0].bitmap[i],
				&win->sprite[0].width, &win->sprite[0].height);
		win->sprite[1].img[i].img = mlx_xpm_file_to_image(win->mlx, win->sprite[1].bitmap[i],
				&win->sprite[1].width, &win->sprite[1].height);
		if (!(win->sprite[0].img[i].img))
			return ;
		i++;
	}
/* 	win->sprite.img->addr = mlx_get_data_addr(win->sprite.img->img,
			&win->sprite.img->bits_x_pixel,
			&win->sprite.img->line_length,
			&win->sprite.img->endian); */
}
