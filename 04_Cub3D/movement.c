/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:34:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/07 14:56:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*movement 1 for forward, -1 for backwards*/
/*COLLITION_DISTANCE garantee that there is no wall in that distance measured*/
void	translate(t_game *game, int movement)
{
	double	move_speed;
	double	new_x;
	double	new_y;
	double	col_x;
	double	col_y;

	move_speed = MOVE_SPEED;
	if (game->player.running && game->player.moving)
		move_speed *= 2;
	new_x = game->map->p_x + movement * game->map->dir_x * move_speed;
	new_y = game->map->p_y + movement * game->map->dir_y * move_speed;
	col_x = game->map->p_x + movement * game->map->dir_x * COLLISION_DISTANCE;
	col_y = game->map->p_y + movement * game->map->dir_y * COLLISION_DISTANCE;
	if (game->map->map[(int)col_y][(int)game->map->p_x] != '1')
		game->map->p_y = new_y;
	if (game->map->map[(int)game->map->p_y][(int)col_x] != '1')
		game->map->p_x = new_x;
}

void	strafing(t_game *game, int movement)
{
	double	move_speed;
	double	new_x;
	double	new_y;
	double	col_x;
	double	col_y;

	move_speed = MOVE_SPEED;
	if (game->player.running && game->player.moving)
		move_speed *= 2;
	new_x = game->map->p_x + movement * game->map->plane_x * move_speed;
	new_y = game->map->p_y + movement * game->map->plane_y * move_speed;
	col_x = game->map->p_x + movement * game->map->plane_x * COLLISION_DISTANCE;
	col_y = game->map->p_y + movement * game->map->plane_y * COLLISION_DISTANCE;
	if (game->map->map[(int)(col_y)][(int)game->map->p_x] != '1')
		game->map->p_y = new_y;
	if (game->map->map[(int)game->map->p_y][(int)(col_x)] != '1')
		game->map->p_x = new_x;
}

/*key 65307 is ESC key*/
int	key_press(int key, t_game *game)
{
	game->player.moving = 1;
	if (key == 65307)
	{
		clean_up_memory(game, 0);
		exit (0);
	}
	if (key == 'D' || key == 'd')
		game->keys.d = 1;
	if (key == 'A' || key == 'a')
		game->keys.a = 1;
	if (key == 'W' || key == 'w')
		game->keys.w = 1;
	if (key == 'S' || key == 's')
		game->keys.s = 1;
	if (key == 65363)
		game->keys.right = 1;
	if (key == 65361)
		game->keys.left = 1;
	if (key == 32)
		game->keys.space = 1;
	if (key == 65505)
		game->keys.shift = 1;
	return (0);
}

/*key 65307 is ESC key*/
int	key_release(int key, t_game *game)
{
	if (key == 'D' || key == 'd')
		game->keys.d = 0;
	if (key == 'A' || key == 'a')
		game->keys.a = 0;
	if (key == 'W' || key == 'w')
		game->keys.w = 0;
	if (key == 'S' || key == 's')
		game->keys.s = 0;
	if (key == 65363)
		game->keys.right = 0;
	if (key == 65361)
		game->keys.left = 0;
	if (key == 32)
		game->keys.space = 0;
	if (key == 65505)
		game->keys.shift = 0;
	if (game->keys.a || game->keys.s || game->keys.d || game->keys.w)
		game->player.moving = 1;
	else
		game->player.moving = 0;
	return (0);
}

/*condition space not pressed has to be here and not in key_release to only
have one jump per space press*/
void	keys_movement(t_game *game)
{
	if (game->keys.w == 1)
		translate(game, 1);
	if (game->keys.s == 1)
		translate(game, -1);
	if (game->keys.d == 1)
		strafing(game, 1);
	if (game->keys.a == 1)
		strafing(game, -1);
	if (game->keys.shift && game->player.moving)
		game->player.running = 1;
	if (game->keys.shift == 0)
		game->player.running = 0;
	if (game->keys.right)
		rotate_camera(game, 1);
	if (game->keys.left)
		rotate_camera(game, -1);
	if (game->keys.space && !game->player.space_was_pressed
		&& !game->player.jumping)
	{
		game->player.jumping = 1;
		game->player.space_was_pressed = 1;
		game->win->ray.i_walking = 0;
	}
	else if (!game->keys.space)
		game->player.space_was_pressed = 0;
}
