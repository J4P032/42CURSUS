/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:01:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/04 19:22:40 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	walking_breathing(t_game *game)
{
	int		breathing;
	//double	new_x;
	//double	new_y;	
	
	breathing = 3;
	ft_memset(CANVAS.addr, 0, WIN_W * WIN_H * (CANVAS.bits_x_pixel / 8));
	if (RAY.i_walking >= 2.0)
		RAY.i_walking = 0;
	if (game->moving == 1)
	{
		breathing = 15;
	}
	RAY.walking_height = breathing * sin(PI * RAY.i_walking);
	RAY.walking_wave = 7 * fabs(cos(PI * RAY.i_walking));
	RAY.i_walking += 0.025;
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
