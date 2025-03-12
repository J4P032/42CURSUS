/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:00:50 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/12 13:20:19 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	movement_horizontal_keys(t_window *win, char c)
{
	if (c == 'r')
	{
		win->sprite->go_right = 1;
		win->sprite->go_down = 0;
		win->sprite->go_left = 0;
		win->sprite->go_up = 0;
	}
	if (c == 'l')
	{
		win->sprite->go_right = 0;
		win->sprite->go_down = 0;
		win->sprite->go_left = 1;
		win->sprite->go_up = 0;
	}
}

void	movement_vertical_keys(t_window *win, char c)
{
	if (c == 'u')
	{
		win->sprite->go_right = 0;
		win->sprite->go_down = 0;
		win->sprite->go_left = 0;
		win->sprite->go_up = 1;
	}
	if (c == 'd')
	{
		win->sprite->go_right = 0;
		win->sprite->go_down = 1;
		win->sprite->go_left = 0;
		win->sprite->go_up = 0;
	}
}

int	key_press(int key, t_window *win)
{
	if (key == XK_space) // LO TENGO QUE QUITAR
		win->running = 0;
	if (key == 65307) //XP_Escape
	{
		mlx_destroy_window(win->mlx, win->win);
		exit (0);
	}
	if (key == XK_d)
		movement_horizontal_keys(win, 'r');
	else if (key == XK_a)
		movement_horizontal_keys(win, 'l');
	else if (key == XK_w)
		movement_vertical_keys(win, 'u');
	else if (key == XK_s)
		movement_vertical_keys(win, 'd');
	return (0);
}
