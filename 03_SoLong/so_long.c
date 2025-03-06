/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:09:02 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/06 13:26:22 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	update_frame(t_window *win)
{
	static int	i;
	static int flag;
	static float	angle2;

	if (!win->running)
		return (0);
		
	if (win->x < WIDTH && win->y < HEIGHT)
		draw_square(&win->canvas, i + win->x, win->y, 0x00000000);
	win->x = WIDTH / 2 + 200 * -1 * sin(win->angle * PI / 180);
	win->y = HEIGHT / 2 + 200 * cos(angle2 * PI / 180);

	angle2 += 0.25f;
	win->angle+=0.5f;
	if (win->angle == 360.0)
		win->angle = 0.0;
	if (i == 0)
		flag = 0;
	if (i == 500)
		flag = 1;
	if (flag == 0)
		i++;

	if (flag == 1)
		i--;

	draw_square(&win->canvas, i + win->x, win->y, 0x00FF0000 - 200 * i);
	mlx_put_image_to_window(win->mlx, win->win, win->canvas.img, 0, 0);
	return (0);
}

int	key_press(int key, t_window *win)
{
	if (key == 32)
		win->running = 0;
	if (key == 65307)
	{
		mlx_destroy_window(win->mlx, win->win);
		exit (0);
	}
	return (0);
}


int main(void)
{
	t_window	win;

	win.win = NULL;
	win.mlx = mlx_init();
	draw_window(&win);
	win.x = WIDTH / 2;
	win.angle = 0;
	win.running = 1;

	mlx_loop_hook(win.mlx, update_frame, &win);
	mlx_key_hook(win.win, key_press, &win);
	mlx_hook(win.win, 17, 0, close_win, win.win);
	mlx_loop(win.mlx);
	return (0);
}
