/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:24:55 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/08 12:32:47 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fps(void)
{
	static int				frame = 0;
	static struct timeval	last_time = {0};
	struct timeval			current_time;
	long					elapsed_ms;

	gettimeofday(&current_time, NULL);
	if (last_time.tv_sec == 0)
		last_time = current_time;
	frame++;
	elapsed_ms = (current_time.tv_sec - last_time.tv_sec) * 1000
		+ (current_time.tv_usec - last_time.tv_usec) / 1000;
	if (elapsed_ms >= 1000)
	{
		write(1, "\rFPS: ", 6);
		ft_putnbr_fd(frame, 1);
		frame = 0;
		last_time = current_time;
	}
}

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

	offset_y = JUMPING - (int)game->win->ray.walking_height;
	bytes_per_line = WIN_W * (game->win->bg.bits_x_pixel / 8);
	y = 0;
	while (y < WIN_H)
	{
		src = game->win->bg.addr
			+ ((y + offset_y) * game->win->bg.line_length);
		dst = game->win->canvas.addr + (y * game->win->canvas.line_length);
		ft_memcpy(dst, src, bytes_per_line);
		y++;
	}
}

/*jumping condition has to be here to produce only one jump per space press*/
void	breathing_walking_running_jumping(t_game *game)
{
	int			breathing;
	int			move_speed;
	t_player	*player;
	t_ray		*ray;

	player = &game->player;
	ray = &game->win->ray;
	breathing = 2;
	move_speed = 1;
	if (player->running && player->moving)
		move_speed = 2;
	if (ray->i_walking >= 2.0)
		ray->i_walking = 0;
	if (player->moving)
		breathing = 7;
	if (player->running && player->moving)
		breathing = 12;
	ray->walking_height = breathing * sin(PI * ray->i_walking * move_speed);
	ray->walking_wave = 4 * (-cos(PI * player->i_wave_walk * move_speed));
	ray->i_walking += 0.025;
	player->i_wave_walk += 0.02;
	if (player->jumping)
		jump(game);
}

/*We send a ray per pixel in WIDTH of the screen
previously I had:
ft_memset(CANVAS.addr, 0, WIN_W * WIN_H * (CANVAS.bits_x_pixel / 8));
to clean the canvas and make knew drawing to not produce artifacts
but now I substitute it with memcpy from the background each frame in
draw_floor_ceiling() */
int	update_frame(t_game *game)
{
	int						x;
	t_data					*canvas;

	x = 0;
	canvas = &game->win->canvas;
	breathing_walking_running_jumping(game);
	keys_action(game);
	if (game->player.mouse_control)
		mlx_hook(game->win->win, MotionNotify, PointerMotionMask,
			mouse_rotation, game);
	else
		mlx_hook(game->win->win, MotionNotify, PointerMotionMask,
			NULL, game);
	draw_floor_ceiling(game);
	while (x < game->win->width)
	{
		raycaster(game, x);
		raycaster_door(game, x++);
	}
	draw_minimap(game);
	mlx_put_image_to_window(game->win->mlx, game->win->win, canvas->img, 0, 0);
	fps();
	if (!game->win->running)
		return (0);
	return (1);
}
