/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:01:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/04 21:07:24 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	walking_breathing(t_game *game)
{
	int	breathing;
	int	move_speed;

	breathing = 2;
	move_speed = 1;
	if (PLAYER.running && PLAYER.moving)
		move_speed = 2;
	ft_memset(CANVAS.addr, 0, WIN_W * WIN_H * (CANVAS.bits_x_pixel / 8));
	if (RAY.i_walking >= 2.0)
		RAY.i_walking = 0;
	if (PLAYER.moving)
		breathing = 7;
	if (PLAYER.running && PLAYER.moving)
		breathing = 12;
	RAY.walking_height = breathing * sin(PI * RAY.i_walking * move_speed); 
	RAY.walking_wave = 4 * (-cos(PI * PLAYER.i_wave_walk * move_speed));
	RAY.i_walking += 0.025;
	PLAYER.i_wave_walk += 0.02;

}

/*We send a ray per pixel in WIDTH of the screen*/
int	update_frame(t_game *game)
{
	//const double	time = 0.03;
	int				x;

	x = 0;
	walking_breathing(game);
	keys_movement(game);
	while (x < game->win->width)
		raycaster(game, x++);
	mlx_put_image_to_window(game->win->mlx, game->win->win, CANVAS.img, 0, 0);
	if (!game->win->running)
		return (0);
	return (1);
}
