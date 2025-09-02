/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:09:25 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/02 14:14:36 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	draw_minimap_frame(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAPSIZE)
	{
		x = 0;
		while (x < MINIMAPSIZE)
		{
			put_pixel(&game->win->canvas, x, y, 0x00000000);
			x++;
		}
		y++;
	}
} */

void	draw_door(t_game *game)
{
	int	x;
	
	x = 0;
	while (x < game->win->width)
		raycaster_door(game, x++);
	
}
