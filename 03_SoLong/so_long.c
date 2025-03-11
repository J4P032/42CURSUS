/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:09:02 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/11 16:48:02 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	update_frame(t_window *win)
{
	static int		i;
	static int		j;

	if (!win->running)
		return (0);
 	/* if (!win->sprite.img.img)
		return (0); */

	if (win->sprite[0].go_right)
	{
		if (win->sprite[0].x > WIDTH - win->sprite[0].width)
			win->sprite[0].x = WIDTH - win->sprite[0].width;
		(win->sprite[0].x)++;
	}
	else if (win->sprite[1].go_right)
	{
		if (win->sprite[0].x > WIDTH - win->sprite[1].width)
			win->sprite[0].x = WIDTH - win->sprite[1].width;
		(win->sprite[0].x)++;
	}
	else if (win->sprite[0].go_left)
	{
		if (win->sprite[0].x < 0)
			win->sprite[0].x = 0;
		(win->sprite[0].x)--;
	}
	else if (win->sprite[1].go_left)
	{
		if (win->sprite[0].x < 0)
			win->sprite[0].x = 0;
		(win->sprite[0].x)--;
	}
	else if (win->sprite[0].go_up)
	{
		if (win->sprite[0].y < 0)
			win->sprite[0].y = 0;
		(win->sprite[0].y)--;
	}
	else if (win->sprite[1].go_up)
	{
		if (win->sprite[0].y < 0)
			win->sprite[0].y = 0;
		(win->sprite[0].y)--;
	}
	else if (win->sprite[0].go_down)
	{
		if (win->sprite[0].y > HEIGHT - win->sprite[0].height)
			win->sprite[0].y = HEIGHT - win->sprite[0].height;
		(win->sprite[0].y)++;
	}
	else if (win->sprite[1].go_down)
	{
		if (win->sprite[0].y > HEIGHT - win->sprite[1].height)
			win->sprite[0].y = HEIGHT - win->sprite[1].height;
		(win->sprite[0].y)++;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->canvas.img, 0, 0);
	if (win->sprite->go_right && win->sprite[0].x > 0 && win->sprite[0].x < WIDTH && win->sprite[0].y > 0 && win->sprite[0].y < HEIGHT)
		mlx_put_image_to_window(win->mlx, win->win, win->sprite[0].img[i].img, win->sprite[0].x, win->sprite[0].y);
	if (win->sprite->go_left)
		mlx_put_image_to_window(win->mlx, win->win, win->sprite[1].img[i].img, win->sprite[0].x, win->sprite[0].y);
	j++;
	if (j == 100)
		i = 1;
	if (j == 200)
		i = 2;
	if (j == 300)
	{
		i = 0;
		j = 0;
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
	load_pacman(&win);
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
