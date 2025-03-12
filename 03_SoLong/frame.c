/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:52:19 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/12 14:29:02 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	scale_time(int *num)
{
	if (*num < 100)
		return (1);
	if (*num > 200 && *num < 300)
		return (2);
	if (*num == 300)
	{
		*num = 0;
		return (0);
	}
	return (0);
}

void	pacman_movement(t_window *win)
{
	if (win->sprite->go_right)
	{
		if (win->sprite[0].x > WIDTH - win->sprite[0].width)
			win->sprite[0].x = WIDTH - win->sprite[0].width;
		(win->sprite[0].x)++;
	}
	else if (win->sprite->go_left)
	{
		if (win->sprite[0].x < 0)
			win->sprite[0].x = 0;
		(win->sprite[0].x)--;
	}
	else if (win->sprite->go_up)
	{
		if (win->sprite[0].y < 0)
			win->sprite[0].y = 0;
		(win->sprite[0].y)--;
	}
	else if (win->sprite->go_down)
	{
		if (win->sprite[0].y > HEIGHT - win->sprite[0].height)
			win->sprite[0].y = HEIGHT - win->sprite[0].height;
		(win->sprite[0].y)++;
	}
}

void	pacman_sprite_anim(t_window *win)
{
	static int		i;
	static int		j;

	mlx_put_image_to_window(win->mlx, win->win, win->canvas.img, 0, 0);
	if (win->sprite->go_right)
		mlx_put_image_to_window(win->mlx, win->win, win->sprite[0].img[i].img,
			win->sprite[0].x, win->sprite[0].y);
	if (win->sprite->go_left)
		mlx_put_image_to_window(win->mlx, win->win, win->sprite[1].img[i].img,
			win->sprite[0].x, win->sprite[0].y);
	if (win->sprite->go_up)
		mlx_put_image_to_window(win->mlx, win->win, win->sprite[2].img[i].img,
			win->sprite[0].x, win->sprite[0].y);
	if (win->sprite->go_down)
		mlx_put_image_to_window(win->mlx, win->win, win->sprite[3].img[i].img,
			win->sprite[0].x, win->sprite[0].y);
	j++;
	i = scale_time(&j);
}

int	update_frame(t_window *win)
{
	if (!win->running)
		return (0);
	pacman_movement(win);
	pacman_sprite_anim(win);
	return (0);
}
