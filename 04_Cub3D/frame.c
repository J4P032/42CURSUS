/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:01:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/05 18:53:42 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	darker_color(int color, float factor)
{
	int r;
	int	g;
	int b;
	
	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	color = (r << 16) | (g << 8) | b;
	return (color);
}


void	draw_floor_ceiling(t_game *game)
{
	int		x;
	int		y;
	float	delta;
	float	factor;

	y = 0;
	if (PLAYER.jumping)
		delta = RAY.walking_height;
	else
		delta = 0;
	RAY.floor_color = 0x006644FF;
	RAY.ceiling_color = 0x00664444;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y < WIN_H / 2 + delta)
			{
				factor = 1.3f * 1.0f - ((float)(y - delta) / (WIN_H / 2));
				if (factor > 1.0f) factor = 1.0f;
				if (factor < 0.0f) factor = 0.0f;
				put_pixel(&game->win->canvas, x, y, darker_color(RAY.ceiling_color, factor));
			}
			else
			{
				factor = 1.3f * (1.0f - ((float)((WIN_H - y) + delta) / (WIN_H / 2)));
				if (factor > 1.0f) factor = 1.0f;
				if (factor < 0.0f) factor = 0.0f;
				put_pixel(&game->win->canvas, x, y, darker_color(RAY.floor_color, factor));
			}
			x++;
		}
		y++;
	}
}


/*jumping condition has to be here to produce only one jump per space press*/
void	breathing_walking_running_jumping(t_game *game)
{
	int	breathing;
	int	move_speed;

	breathing = 2;
	move_speed = 1;
	if (PLAYER.running && PLAYER.moving)
		move_speed = 2;
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
	if (PLAYER.jumping)
		jump(game);
}

/*We send a ray per pixel in WIDTH of the screen*/
/*memset cleans the screen quick to reflect change in new drawing*/
int	update_frame(t_game *game)
{
	//const double	time = 0.03;
	int				x;

	x = 0;
	ft_memset(CANVAS.addr, 0, WIN_W * WIN_H * (CANVAS.bits_x_pixel / 8));
	breathing_walking_running_jumping(game);
	keys_movement(game);
	draw_floor_ceiling(game);
	while (x < game->win->width)
		raycaster(game, x++);
	mlx_put_image_to_window(game->win->mlx, game->win->win, CANVAS.img, 0, 0);
	if (!game->win->running)
		return (0);
	return (1);
}
