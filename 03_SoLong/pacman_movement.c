/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pacman_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 08:56:39 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/20 17:40:56 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	next_wall_ver(t_game *game)
{
	int	i;
	int	j;
	int	j_right;

	i = game->win->sprite[0].i;
	j = game->win->sprite[0].j;
	j_right = (game->win->sprite[0].x + SPRITE_WIDTH - 1) / SPRITE_WIDTH;
	if (game->win->sprite->go_up)
	{
		while (game->map->map[i][j] != '1'
			&& game->map->map[i][j_right] != '1' && i > 0)
			i--;
		return ((i * SPRITE_HEIGHT) + SPRITE_HEIGHT);
	}
	while (game->map->map[i][j] != '1'
		&& game->map->map[i][j_right] != '1' && i < game->win->height - 1)
		i++;
	return (i * SPRITE_HEIGHT);
}

int	next_wall_hor(t_game *game)
{
	int	i;
	int	j;
	int	i_bottom;

	i = game->win->sprite[0].i;
	j = game->win->sprite[0].j;
	i_bottom = (game->win->sprite[0].y + SPRITE_HEIGHT - 1) / SPRITE_HEIGHT;
	if (game->win->sprite->go_right)
	{
		while (game->map->map[i][j] != '1'
			&& game->map->map[i_bottom][j] != '1' && j < game->win->width - 1)
			j++;
		return (j * SPRITE_WIDTH);
	}
	while (game->map->map[i][j] != '1'
		&& game->map->map[i_bottom][j] != '1' && j > 0)
		j--;
	return ((j * SPRITE_WIDTH) + SPRITE_WIDTH);
}

void	pacman_vertical_movement(t_game *game)
{
	int	wall_y;

	wall_y = next_wall_ver(game);
	if (game->win->sprite->go_up)
	{
		if (game->win->sprite[0].y <= wall_y)
			game->win->sprite[0].y = wall_y;
		else
			(game->win->sprite[0].y)--;
	}
	else if (game->win->sprite->go_down)
	{
		if (game->win->sprite[0].y + SPRITE_HEIGHT >= wall_y)
			game->win->sprite[0].y = wall_y - SPRITE_HEIGHT;
		else
			(game->win->sprite[0].y)++;
	}
}

void	pacman_horizontal_movement(t_game *game)
{
	int	wall_x;

	wall_x = next_wall_hor(game);
	if (game->win->sprite->go_right)
	{
		if (game->win->sprite[0].x + SPRITE_WIDTH >= wall_x)
			game->win->sprite[0].x = wall_x - SPRITE_WIDTH;
		else
			(game->win->sprite[0].x)++;
	}
	else if (game->win->sprite->go_left)
	{
		if (game->win->sprite[0].x <= wall_x)
			game->win->sprite[0].x = wall_x;
		else
			(game->win->sprite[0].x)--;
	}
}

void	pacman_iddle(t_game *game)
{
	if (game->win->sprite->go_right == 0 && game->win->sprite->go_left == 0
		&& game->win->sprite->go_up == 0 && game->win->sprite->go_down == 0)
	{
		mlx_put_image_to_window(game->win->mlx, game->win->win,
			game->win->sprite[0].img[1].img,
			game->win->sprite[0].x,
			game->win->sprite[0].y);
	}
	else
	{
		game->win->sprite[0].j = game->win->sprite[0].x / SPRITE_WIDTH;
		game->win->sprite[0].i = game->win->sprite[0].y / SPRITE_HEIGHT;
		pacman_horizontal_movement(game);
		pacman_vertical_movement(game);
	}
}
