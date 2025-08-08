/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:31:57 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/08 13:44:00 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_frame(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < 150)
	{
		x = 0;
		while (x < 150)
		{
			put_pixel(&game->win->canvas, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	draw_minimap_frame(game);


}
