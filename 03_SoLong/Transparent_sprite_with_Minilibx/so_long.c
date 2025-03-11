/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:09:02 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/11 09:32:06 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	update_frame(t_window *win)
{
	static int		i;
	static int		flag;
	static float	angle2;

	if (!win->running)
		return (0);
/*  	if (!win->sprite.img.img)
		return (0); */
	if (win->x < 1920 && win->x > 0 && win->y < 1080 && win->y > 0)
	{	//draw_square(&win->canvas, i + win->x, win->y, 0x00000000);
		//draw_circle(&win->canvas, i + win->x, win->y, i / 4, 0x00000000);
		erase_transparent_sprite(win, win->x, win->y);
	}
	win->x = WIDTH / 2 + 200 * -1 * sin(win->angle * PI / 180);
	win->y = HEIGHT / 2 + 200 * cos(angle2 * PI / 180);


	//mlx_put_image_to_window(win->mlx, win->win, win->buffer.img, 0, 0);

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

	//draw_square(&win->canvas, i + win->x, win->y, 0x00FF0000 - 200 * i);
	draw_circle(&win->canvas, WIDTH / 2, HEIGHT / 2, i / 4, 0x00FF0000 - 200 * i);
	//draw_circle(&win->canvas, i + win->x, win->y, i / 4, 0x00FF0000 - 200 * i);
	mlx_put_image_to_window(win->mlx, win->win, win->canvas.img, 0, 0);
	draw_transparent_sprite(win, win->x, win->y);
	//mlx_put_image_to_window(win->mlx, win->win, win->sprite.img.img, win->x, win->y);
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

/* int	print_msg(int keycode, void *param)
{
	(void)keycode;
	(void)param;
	write(1, "hola\n", 5);
	return (0);
} */


int main(void)
{
	t_window	win;

	win.win = NULL;
	win.mlx = mlx_init();
	draw_window(&win);
	draw_sprite(&win);
	win.x = WIDTH / 2;
	win.angle = 0;
	win.running = 1;

	mlx_loop_hook(win.mlx, update_frame, &win);
	mlx_key_hook(win.win, key_press, &win);
	//mlx_hook(win.win, 2, 1L<<0 | 1L<<1, print_msg, &win);
	mlx_hook(win.win, 17, 0, close_win, &win);
	mlx_loop(win.mlx);
	return (0);
}
