/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:44:09 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/17 16:12:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

/*just one enemy 'x' allowed, if more return 1, else 0*/
int	enemy_position(t_game *game, size_t x, size_t y)
{
	srand(time(NULL));
	while (y < game->map->lines)
	{
		x = 0;
		while (x < game->map->columns)
		{
			if (game->map->map[y][x] == 'x')
			{
				game->enemy.num_enemies++;
				if (game->enemy.num_enemies > 1)
					return (1);
				game->enemy.e_x = x + 0.5;
				game->enemy.e_y = y + 0.5;
				game->enemy.number_hits = 0;
				game->enemy.go_down = 0;
				game->enemy.time = 0;
			}
			x++;
		}
		y++;
	}
	return (0);
}

/*We want to transform the sprite vector in the world (e_dx, e_dy) to camera...
...coordinates (trans_x, trans_y), and that is a matrix formula:

⎡trans_x⎤ = M-¹ * ⎡e_dx⎤
⎣trans_y⎦	      ⎣e_dy⎦

M-¹ = 1 / det(M) ⎡plane_y  -plane_x⎤
                 ⎣-dir_y   -dir_x  ⎦

det(M) =  dir_x * plane_y - dir_y * plane_x 

inv_det = 1 / det(M)
but I change to det(M) = - dir_x * plane_y + dir_y * plane_x because invert
to make it appear in screen, because hidding behind wall corners.

if (trans_y <= 0.0) return; if sprite is behind camera don't calculate.

if (sprite_size > WIN_H * 2) sprite_size = WIN_H * 2; to not force high spend...
in performance.
Last return is to not glue the sprite when moving camera to border of screen*/
void	calculate_screen_pos_size(t_game *game, double dx, double dy, int i)
{
	t_map	*map;
	double	inv_det;
	double	trans_x;
	double	trans_y;
	int		sprite_size;

	map = game->map;
	inv_det = 1.0 / (map->plane_x * map->dir_y - map->dir_x * map->plane_y);
	trans_x = inv_det * (map->dir_y * dx - map->dir_x * dy);
	trans_y = inv_det * (-map->plane_y * dx + map->plane_x * dy);
	if (trans_y <= 0.0)
		return ;
	sprite_size = (int)fabs(WIN_H / trans_y);
	if (sprite_size > WIN_H * 2)
		sprite_size = WIN_H * 2;
	game->enemy.sprite_size = sprite_size;
	game->enemy.screen_x = (int)((WIN_W / 2) * (1 + trans_x / trans_y))
		- game->enemy.sprite_size / 2 + cos(i) * game->enemy.sprite_size / 9.9f;
	game->enemy.screen_y = -game->enemy.sprite_size / 2 + WIN_H / 2
		+ game->win->ray.walking_height
		+ sin(i) * game->enemy.sprite_size / 20.0f;
	if (game->enemy.screen_x + game->enemy.sprite_size < 0
		|| game->enemy.screen_x >= WIN_W
		|| game->enemy.screen_y + game->enemy.sprite_size < 0)
		return ;
}

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
void	reposition_enemy(t_game *game)
{
	int	x;
	int	y;
	
	if (game->enemy.time % 5 == 0 && !game->enemy.despawn)
	{
		x = (int)(((double)rand() / RAND_MAX) * game->map->columns);
		y = (int)(((double)rand() / RAND_MAX) * game->map->lines);
		if (game->map->map[y][y] == '0') //CUIDADO QUE EL PARSEO NO PONGA 0 FUERA DEL MAPA Y POR LO TANTO SEGFAULT
		{
			game->enemy.e_x = x + 0.5;
			game->enemy.e_y = y + 0.5;
			game->enemy.despawn = 1;
		}
	}
}

void	move_enemy(t_game *game, size_t x, size_t y)
{
	x = (size_t)floor(game->enemy.e_x);
	y = (size_t)floor(game->enemy.e_y);
	if (x == 0 || y == 0 || x >= game->map->columns || y >= game->map->lines)
		x = 1; //revisar si no desaparece el fantasma. antes era return; el problema era con x = 0
	game->enemy.angle = ((double)rand() / RAND_MAX) * (0.04 - 0.01) + 0.01;
	if (game->map->map[y][x + 1] == '1' && game->enemy.number_hits % 2 == 0)
	{
		if (game->map->map[y + 1][x] != '1')
			game->enemy.go_down = 1;
		else if (game->map->map[y - 1][x] != '1')
			game->enemy.go_down = 0;
		game->enemy.number_hits++;
	}
	else if (game->map->map[y][x - 1] == '1' && game->enemy.number_hits % 2 != 0)
		game->enemy.number_hits++;
	if (game->enemy.number_hits % 2 == 0)
		game->enemy.e_x += 0.05;
	else
		game->enemy.e_x -= 0.05;
	if (game->enemy.go_down && game->map->map[y + 1][x] != '1')
		game->enemy.e_y += 0.05 + game->enemy.angle;
	else if (game->map->map[y - 1][x] != '1')
		game->enemy.e_y -= 0.05 - game->enemy.angle;
	reposition_enemy(game);
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
		draw_enemy_on_canvas(game, game->win->sprite[18], foe->screen_x,
			foe->screen_y);
		reset_enemy_view_matrix(game);
	}
}
