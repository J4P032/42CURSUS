/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:08:09 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/05 10:06:39 by jrollon-         ###   ########.fr       */
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
	angle = direction * (2 * PI * ROTATION_SPEED / 360);
	MAP->dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
	MAP->dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);
	MAP->plane_x = -MAP->dir_y * RAY.fov_factor;
	MAP->plane_y = MAP->dir_x * RAY.fov_factor;
}
