/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:04:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/11 16:46:38 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
void	load_pacman(t_window *win)
{
	size_t	i;

	i = 0;
	win->sprite[0].bitmap[0] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_r_00.xpm";
	win->sprite[0].bitmap[1] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_r_01.xpm";
	win->sprite[0].bitmap[2] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_r_02.xpm";
	win->sprite[1].bitmap[0] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_l_00.xpm";
	win->sprite[1].bitmap[1] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_l_01.xpm";
	win->sprite[1].bitmap[2] = "/home/jrollon-/Desktop/CURSUS/03_SoLong/sprites/pacman_l_02.xpm";
	while (i < 2)
	{
		win->sprite[i].width = 64;
		win->sprite[i].height = 64;
		win->sprite[i].x = (WIDTH / 2) - win->sprite[i].width / 2;
		win->sprite[i].y = (HEIGHT / 2)- win->sprite[i].height / 2;
		win->sprite[i].go_up = 0;
		win->sprite[i].go_right = 0;
		win->sprite[i].go_down = 0;
		win->sprite[i].go_left = 0;
		i++;
	}
	i = 0;
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
}
