/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:12:33 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/10 10:50:30 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_win(void *param)
{
	t_window	*win;
	win = (t_window *)param;
	mlx_destroy_window(win->mlx, win->win);
	return (0);
}

void	draw_window(t_window *win)
{
	if (!(win)->win)
		(win)->win = mlx_new_window((win)->mlx, WIDTH, HEIGHT, "So Long");
	(win)->canvas.img = mlx_new_image((win)->mlx, WIDTH, HEIGHT);
	(win)->canvas.addr = mlx_get_data_addr((win)->canvas.img,
			&(win)->canvas.bits_x_pixel,
			&(win)->canvas.line_length,
			&(win)->canvas.endian);
}
