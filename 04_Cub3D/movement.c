/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:34:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/04 17:30:59 by jrollon-         ###   ########.fr       */
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
	if (key == 65307)
	{
		clean_up_memory(game);
		exit (0);
	}
	if (key == 'D' || key == 'd') // || key == 65363 flecha dcha)
		strafing(game, 1);
	else if (key == 'A' || key == 'a') // || key == 65361 flecha izda)
		strafing(game, -1);
	else if (key == 'W' || key == 'w') //  || key == 65362 flecha arriba)
		translate(game, 1);
	else if (key == 'S' || key == 's') // || key == 65364 flecha abajo)
		translate(game, -1);
	return (0);
}
