/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:08:09 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/24 15:32:02 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*angle in radians with ROTATION_SPEED in degrees*/
void	rotate_camera(t_game *game, int direction)
{
	double	angle;
	double	old_dir_x;
	double	old_dir_y;

	old_dir_x = game->map->dir_x;
	old_dir_y = game->map->dir_y;
	angle = direction * game->win->ray.rotation_speed;
	game->map->dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
	game->map->dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);
	game->map->plane_x = -game->map->dir_y * game->win->ray.fov_factor;
	game->map->plane_y = game->map->dir_x * game->win->ray.fov_factor;
}

int	mouse_rotation(int x, int y, t_game *game)
{
	static int	skip = 0;
	double		sensitivity;
	int			center_x;
	int			delta;

	(void)y;
	center_x = WIN_W / 2;
	sensitivity = 0.05;
	if (skip)
	{
		skip = 0;
		return (0);
	}
	if (x != center_x && game->player.mouse_control)
	{
		delta = x - center_x;
		rotate_camera(game, delta * sensitivity);
		skip = 1;
		mlx_mouse_move(game->win->mlx, game->win->win, WIN_W / 2, WIN_H / 2);
	}
	return (0);
}

void	keys_rotation(t_game *game)
{
	if (game->keys.right)
		rotate_camera(game, 1);
	if (game->keys.left)
		rotate_camera(game, -1);
}
