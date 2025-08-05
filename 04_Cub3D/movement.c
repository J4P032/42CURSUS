/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:34:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/05 10:07:31 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*movement 1 for forward, -1 for backwards*/
void	translate(t_game *game, int movement)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = MOVE_SPEED;
	if (PLAYER.running && PLAYER.moving)
		move_speed *= 2;
	new_x = MAP->p_x + movement * MAP->dir_x * move_speed;
	new_y = MAP->p_y + movement * MAP->dir_y * move_speed;
	if (MAP->map[(int)new_y][(int)MAP->p_x] != '1')
		MAP->p_y = new_y;
	if (MAP->map[(int)MAP->p_y][(int)new_x] != '1')
		MAP->p_x = new_x;
}

void	strafing(t_game *game, int movement)
{
	double	move_speed;
	double	new_x;
	double	new_y;
	
	move_speed = MOVE_SPEED;
	if (PLAYER.running && PLAYER.moving)
		move_speed *= 2;
	new_x = MAP->p_x + movement * MAP->plane_x * move_speed;
	new_y = MAP->p_y + movement * MAP->plane_y * move_speed;
	if (MAP->map[(int)new_y][(int)MAP->p_x] != '1')
		MAP->p_y = new_y;
	if (MAP->map[(int)MAP->p_y][(int)new_x] != '1')
		MAP->p_x = new_x;
}


/*key 65307 is ESC key*/
int	key_press(int key, t_game *game)
{
	PLAYER.moving = 1;
	if (key == 65307)
	{
		clean_up_memory(game);
		exit (0);
	}
	if (key == 'D' || key == 'd')
		KEY.d = 1;
	if (key == 'A' || key == 'a')
		KEY.a = 1;
	if (key == 'W' || key == 'w')
		KEY.w = 1;
	if (key == 'S' || key == 's') 
		KEY.s = 1;
	if (key == 65363)
		KEY.right = 1;
	if (key == 65361)
		KEY.left = 1;
	if (key == 32)
		KEY.space = 1;
	if (key == 65505)
		KEY.shift = 1;
	return (0);
}

/*key 65307 is ESC key*/
int	key_release(int key, t_game *game)
{
	if (key == 'D' || key == 'd')
		KEY.d = 0;
	if (key == 'A' || key == 'a')
		KEY.a = 0;
	if (key == 'W' || key == 'w')
		KEY.w = 0;
	if (key == 'S' || key == 's') 
		KEY.s = 0;
	if (key == 65363)
		KEY.right = 0;
	if (key == 65361)
		KEY.left = 0;
	if (key == 32)
		KEY.space = 0;
	if (key == 65505)
		KEY.shift = 0;
	if (KEY.a || KEY.s || KEY.d || KEY.w)
		PLAYER.moving = 1;
	else
		PLAYER.moving = 0;
	return (0);
}

void	keys_movement(t_game *game)
{
	if (KEY.w == 1)
		translate(game, 1);
	if (KEY.s == 1)
		translate(game, -1);
	if (KEY.d == 1)
		strafing(game, 1);
	if (KEY.a == 1)
		strafing(game, -1);
	if (KEY.shift && PLAYER.moving)
		PLAYER.running = 1;
	if (KEY.shift == 0)
		PLAYER.running = 0;
	if (KEY.right)
		rotate_camera(game, 1);
	if (KEY.left)
		rotate_camera(game, -1);
}
