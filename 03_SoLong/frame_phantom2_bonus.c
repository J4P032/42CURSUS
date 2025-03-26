/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_phantom2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:06:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/25 10:42:16 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	phantom_go_up(t_game *game, int n, char g)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < game->map->lines)
	{
		j = 0;
		while (j < game->map->columns)
		{
			if (game->map_cpy[i][j] == g)
			{
				game->win->sprite[n].i = i;
				game->win->sprite[n].j = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	phantom_go_down(t_game *game, int n, char g)
{
	size_t	i;
	size_t	j;

	i = game->map->lines - 2;
	while (i > 0)
	{
		j = game->map->columns - 2;
		while (j > 0)
		{
			if (game->map_cpy[i][j] == g)
			{
				game->win->sprite[n].i = i;
				game->win->sprite[n].j = j;
				return ;
			}
			j--;
		}
		i--;
	}
}

int	next_wall_ver2(t_game *game, int n)
{
	int	i;
	int	j;
	int	j_right;

	i = game->win->sprite[n].y / SPRITE_HEIGHT;
	j = game->win->sprite[n].x / SPRITE_WIDTH;
	j_right = (game->win->sprite[n].x + SPRITE_WIDTH - 1) / SPRITE_WIDTH;
	if (game->win->sprite[n].go_up == 'u')
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

int	next_wall_hor2(t_game *game, int n)
{
	int	i;
	int	j;
	int	i_bottom;

	i = game->win->sprite[n].y / SPRITE_HEIGHT;
	j = game->win->sprite[n].x / SPRITE_WIDTH;
	i_bottom = (game->win->sprite[n].y + SPRITE_HEIGHT - 1) / SPRITE_HEIGHT;
	if (game->win->sprite[n].go_up == 'r')
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

void	ghost_vertical_movement(t_game *game, int n)
{
	int	wall_y;

	wall_y = next_wall_ver2(game, n);
	if (game->win->sprite[n].go_up == 'u')
	{
		if (game->win->sprite[n].y <= wall_y)
			game->win->sprite[n].y = wall_y;
		else
			(game->win->sprite[n].y)--;
	}
	else if (game->win->sprite[n].go_up == 'd')
	{
		if (game->win->sprite[n].y + SPRITE_HEIGHT >= wall_y)
			game->win->sprite[n].y = wall_y - SPRITE_HEIGHT;
		else
			(game->win->sprite[n].y)++;
	}
}
