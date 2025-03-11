/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:09:02 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/11 15:03:39 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	update_frame(t_window *win)
{
	static int		j;
	static int		i;
	static int		k;
	static int		flag;
	static float	angle2;
	static int	x;
	static int	y;

	if (!win->running)
		return (0);
 	/* if (!win->sprite.img.img)
		return (0); */
	if (win->x < 1920 && win->x > 0 && win->y < 1080 && win->y > 0)
		//draw_square(&win->canvas, j + win->x, win->y, 0x00000000);
		draw_circle(&win->canvas, j + win->x, win->y, j / 4, 0x00000000);
	win->x = WIDTH / 2 + 200 * -1 * sin(win->angle * PI / 180);
	win->y = HEIGHT / 2 + 200 * cos(angle2 * PI / 180);

	//mlx_put_image_to_window(win->mlx, win->win, win->buffer.img, 0, 0);
	angle2 += 0.25f;
	win->angle+=0.5f;
	if (win->angle == 360.0)
		win->angle = 0.0;
	if (j == 0)
		flag = 0;
	if (j == 500)
		flag = 1;
	if (flag == 0)
		j++;
	if (flag == 1)
		j--;

	if (win->sprite[0].go_right)
	{
		if (x > WIDTH - win->sprite[0].width)
			x = WIDTH - win->sprite[0].width;
		x++;
	}
	if (win->sprite[1].go_right)
	{
		if (x > WIDTH - win->sprite[1].width)
			x = WIDTH - win->sprite[1].width;
		x++;
	}
	else if (win->sprite[0].go_left)
	{
		if (x < 0)
			x = 0;
		x--;
	}
	else if (win->sprite[1].go_left)
	{
		if (x < 0)
			x = 0;
		x--;
	}
	else if (win->sprite[0].go_up)
	{
		if (y < 0)
			y = 0;
		y--;
	}
	else if (win->sprite[1].go_up)
	{
		if (y < 0)
			y = 0;
		y--;
	}
	else if (win->sprite[0].go_down)
	{
		if (y > HEIGHT - win->sprite[0].height)
			y = HEIGHT - win->sprite[0].height;
		y++;
	}
	else if (win->sprite[1].go_down)
	{
		if (y > HEIGHT - win->sprite[1].height)
			y = HEIGHT - win->sprite[1].height;
		y++;
	}

	//draw_square(&win->canvas, j + win->x, win->y, 0x00FF0000 - 200 * j);
	draw_circle(&win->canvas, j + win->x, win->y, j / 4, 0x00FF0000 - 200 * j);

	mlx_put_image_to_window(win->mlx, win->win, win->canvas.img, 0, 0);
	//draw_transparent_sprite(win);
	if (win->sprite->go_right)
		mlx_put_image_to_window(win->mlx, win->win, win->sprite[0].img[i].img, x, y);
	if (win->sprite->go_left)
		mlx_put_image_to_window(win->mlx, win->win, win->sprite[1].img[i].img, x, y);
	k++;
	if (k == 100)
		i = 1;
	if (k == 200)
		i = 2;
	if (k == 300)
	{
		i = 0;
		k = 0;
	}

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
	if (key == 68 || key == 100)
	{
		win->sprite[0].go_right = 1;
		win->sprite[0].go_down = 0;
		win->sprite[0].go_left = 0;
		win->sprite[0].go_up = 0;
		win->sprite[1].go_right = 1;
		win->sprite[1].go_down = 0;
		win->sprite[1].go_left = 0;
		win->sprite[1].go_up = 0;
	}
	else if (key == 65 || key == 97)
	{
		win->sprite[0].go_right = 0;
		win->sprite[0].go_down = 0;
		win->sprite[0].go_left = 1;
		win->sprite[0].go_up = 0;

		win->sprite[1].go_right = 0;
		win->sprite[1].go_down = 0;
		win->sprite[1].go_left = 1;
		win->sprite[1].go_up = 0;
	}
	else if (key == 87 || key == 119)
	{
		win->sprite[0].go_right = 0;
		win->sprite[0].go_down = 0;
		win->sprite[0].go_left = 0;
		win->sprite[0].go_up = 1;

		win->sprite[1].go_right = 0;
		win->sprite[1].go_down = 0;
		win->sprite[1].go_left = 0;
		win->sprite[1].go_up = 1;
	}
	else if (key == 83 || key == 115)
	{
		win->sprite[0].go_right = 0;
		win->sprite[0].go_down = 1;
		win->sprite[0].go_left = 0;
		win->sprite[0].go_up = 0;

		win->sprite[1].go_right = 0;
		win->sprite[1].go_down = 1;
		win->sprite[1].go_left = 0;
		win->sprite[1].go_up = 0;
	}

	return (0);
}


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
