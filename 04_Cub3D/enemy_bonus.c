/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:58:39 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/29 19:18:01 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

/*This function reset all the matrix of green pixels to 1 so allow view...
of the enemy sprite once the first door hit is not found and reset to...
1 the 0 that wasn't green pixels in the door texture*/
void	reset_enemy_view_matrix(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			game->win->ray.green_pixel[x][y] = 1;
			x++;
		}
		y++;
	}
}

/*The enemy will despawn each 5 seconds and will respawn in any random place...
...in the map.*/
void	reposition_enemy(t_game *game, int x, int y)
{
	int	px;
	int	py;

	x = (int)floor(game->enemy.e_x);
	y = (int)floor(game->enemy.e_y);
	px = (int)floor(game->map->p_x);
	py = (int)floor(game->map->p_y);
	if (x == px && y == py)
	{
		clean_up_memory(game, 0);
		printf("\n*************** YOU DIED!!! ***************\n");
		exit (0);
	}
	if (game->enemy.time % 5 == 0 && !game->enemy.despawn)
	{
		x = (int)(((double)rand() / RAND_MAX) * game->map->columns);
		y = (int)(((double)rand() / RAND_MAX) * game->map->lines);
		if (game->map->map[y][x] == '0')
		{
			game->enemy.e_x = x + 0.5;
			game->enemy.e_y = y + 0.5;
			game->enemy.despawn = 1;
		}
	}
}

static void	handle_enemy_movement(t_game *game, size_t x, size_t y)
{
	if (game->map->map[y][x + 1] == '1' && game->enemy.number_hits % 2 == 0)
	{
		if (game->map->map[y + 1][x] != '1')
			game->enemy.go_down = 1;
		else if (game->map->map[y - 1][x] != '1')
			game->enemy.go_down = 0;
		game->enemy.number_hits++;
	}
	else if (game->map->map[y][x - 1] == '1'
		&& game->enemy.number_hits % 2 != 0)
		game->enemy.number_hits++;
	if (game->enemy.number_hits % 2 == 0)
		game->enemy.e_x += 0.05;
	else
		game->enemy.e_x -= 0.05;
	if (game->enemy.go_down && game->map->map[y + 1][x] != '1')
		game->enemy.e_y += 0.05 + game->enemy.angle;
	else if (game->map->map[y - 1][x] != '1')
		game->enemy.e_y -= 0.05 - game->enemy.angle;
}

void	move_enemy(t_game *game, size_t x, size_t y)
{
	x = (size_t)floor(game->enemy.e_x);
	y = (size_t)floor(game->enemy.e_y);
	if (x == 0 || y == 0 || x >= game->map->columns
		|| y >= game->map->lines)
		x = 1;
	game->enemy.angle = ((double)rand() / RAND_MAX) * (0.04 - 0.01) + 0.01;
	handle_enemy_movement(game, x, y);
	reposition_enemy(game, 0, 0);
}

/*By pythagoras we have distance from dx and dy
I want only to load enemy position once for performance so that is for...
...enemy.loaded. Also once if enemy not moving calculate the distance...
...with updated_dist*/
void	enemy(t_game *game)
{
	double	e_dx;
	double	e_dy;
	t_enemy	*foe;

	foe = &game->enemy;
	e_dx = game->enemy.e_x - game->map->p_x;
	e_dy = game->enemy.e_y - game->map->p_y;
	if (!game->enemy.loaded && enemy_position(game, 0, 0))
	{
		perror("Error: This game don't allow more than one enemy");
		clean_up_memory(game, 0);
		exit (1);
	}
	game->enemy.loaded = 1;
	game->enemy.e_dist = sqrt(e_dx * e_dx + e_dy * e_dy);
	if (game->enemy.num_enemies == 1)
	{
		move_enemy(game, 0, 0);
		calculate_screen_pos_size(game, e_dx, e_dy, game->enemy.float_index);
		game->enemy.float_index += 0.2f;
		if (game->enemy.visible)
			draw_enemy_on_canvas(game, game->win->sprite[18], foe->screen_x,
				foe->screen_y);
		reset_enemy_view_matrix(game);
	}
}
