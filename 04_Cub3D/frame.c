/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:01:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/06 12:33:37 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* offset_y is vertical pixels we are going to copy. We need num bytes of each
line. For that we need the source to be copied, 
WIN->background.line_length is number of bytes of a full row of img in memory
as with bytes_per_line but can include padding (free space to match memory)
(y + offset_y) tells which line we want to copy. So we advance in memory up to
the correct address of the line to be copied.
dst is the memory address in CANVAS buffer where we copy those lines*/
void	draw_floor_ceiling(t_game *game)
{
	int		offset_y;
	int		y;
	char	*src;
	char	*dst;
	int		bytes_per_line;

	offset_y = JUMPING - (int)RAY.walking_height;
	bytes_per_line = WIN_W * (game->win->background.bits_x_pixel / 8);
	y = 0;
	while (y < WIN_H)
	{
		src = WIN->background.addr + 
			((y + offset_y) * WIN->background.line_length);
		dst = CANVAS.addr + (y * CANVAS.line_length);
		ft_memcpy(dst, src, bytes_per_line);
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
int	update_frame(t_game *game)
{
	//const double	time = 0.03;
	int				x;

	x = 0;

	//ft_memset(CANVAS.addr, 0, WIN_W * WIN_H * (CANVAS.bits_x_pixel / 8));
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
