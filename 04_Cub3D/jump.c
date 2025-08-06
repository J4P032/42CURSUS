/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:12:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/06 16:14:44 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	jump(t_game *game)
{
	t_ray	*ray;

	ray = &game->win->ray;
	ray->walking_height = JUMPING * fabs(sin(PI * ray->i_walking));
	ray->i_walking += 0.005;
	if (ray->i_walking >= 1)
	{
		game->player.jumping = 0;
		ray->walking_height = 0;
	}
}
