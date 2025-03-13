/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:00:50 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/13 17:36:45 by jrollon-         ###   ########.fr       */
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
	if (key == ' ') // LO TENGO QUE QUITAR
		win->running = 0;
	if (key == 65307) //XP_Escape
	{
		clean_up_memory(win);
		exit (0);
	}
	if (key == 'D' || key == 'd' || key == 65363)
		movement_horizontal_keys(win, 'r');
	else if (key == 'A' || key =='a' || key == 65361)
		movement_horizontal_keys(win, 'l');
	else if (key == 'W' || key == 'w' || key == 65362)
		movement_vertical_keys(win, 'u');
	else if (key == 'S' || key == 's' || key == 65364)
		movement_vertical_keys(win, 'd');
	return (0);
}
