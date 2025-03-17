/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:00:50 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/17 17:22:04 by jrollon-         ###   ########.fr       */
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

void	pre_movement(t_game *game)
{
	int	i;
	int	j;


	if (game->win->sprite->go_right)
	{
		i = game->win->sprite[0].i;
		j = game->win->sprite[0].x / SPRITE_WIDTH;
	}

	if (game->win->sprite->go_left)
	{
		i = game->win->sprite[0].i;
		j = (game->win->sprite[0].x + SPRITE_WIDTH - 1) / SPRITE_WIDTH;
	}

	if (game->win->sprite->go_up)
	{
		i = (game->win->sprite[0].y + SPRITE_HEIGHT - 1) / SPRITE_HEIGHT;
		j = game->win->sprite[0].x / SPRITE_WIDTH;
	}

	if (game->win->sprite->go_down)
	{
		i = game->win->sprite[0].y / SPRITE_HEIGHT;
		j = game->win->sprite[0].x / SPRITE_WIDTH;
	}



	if (game->win->sprite->desired_dir == 'r')
	{
		if (game->map->map[i][j + 1] != '1')
			movement_horizontal_keys(game->win, 'r');
	}
	if (game->win->sprite->desired_dir == 'l')
	{
		if (game->map->map[i][j - 1] != '1')
			movement_horizontal_keys(game->win, 'l');
	}
	if (game->win->sprite->desired_dir == 'u')
	{
		if (game->map->map[i - 1][j] != '1')
			movement_vertical_keys(game->win, 'u');
	}
	if (game->win->sprite->desired_dir == 'd')
	{
		if (game->map->map[i + 1][j] != '1')
			movement_vertical_keys(game->win, 'd');
	}
}

int	key_press(int key, t_game *game)
{
	if (key == ' ') // LO TENGO QUE QUITAR
		game->win->running = 0;
	if (key == 65307) //XP_Escape
	{
		clean_up_memory(game);
		exit (0);
	}
	if (key == 'D' || key == 'd' || key == 65363)
		game->win->sprite->desired_dir = 'r';
		//movement_horizontal_keys(game->win, 'r');
	else if (key == 'A' || key =='a' || key == 65361)
		game->win->sprite->desired_dir = 'l';
		//movement_horizontal_keys(game->win, 'l');
	else if (key == 'W' || key == 'w' || key == 65362)
		game->win->sprite->desired_dir = 'u';
		//movement_vertical_keys(game->win, 'u');
	else if (key == 'S' || key == 's' || key == 65364)
		game->win->sprite->desired_dir = 'd';
		//movement_vertical_keys(game->win, 'd');

	//printf("deseo: %c\n", (char)game->win->sprite->desired_dir);//

	return (0);
}
