/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:08:09 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/05 11:25:56 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*angle in radians with ROTATION_SPEED in degrees*/
void	rotate_camera(t_game *game, int direction)
{
	double	angle;
	double	old_dir_x;
	double	old_dir_y;

	old_dir_x = MAP->dir_x;
	old_dir_y = MAP->dir_y;
	angle = direction * RAY.rotation_speed;
	MAP->dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
	MAP->dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);
	MAP->plane_x = -MAP->dir_y * RAY.fov_factor;
	MAP->plane_y = MAP->dir_x * RAY.fov_factor;
}

int	mouse_rotation(int x, int y, t_game *game)
{
	static int	skip = 0;
	double		sensitivity;
	int 		center_x;
	int			delta;

	(void)y;
	center_x = WIN_W / 2;
	sensitivity = 0.05;
	if (skip)
	{
		skip = 0;
		return (0);
	}
	if (x != center_x)
	{
		delta = x - center_x;
		rotate_camera(game, delta * sensitivity);
		skip = 1;
		mlx_mouse_move(game->win->mlx, game->win->win, WIN_W / 2, WIN_H / 2);
	}
	return (0);
}
