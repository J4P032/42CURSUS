/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:01:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/05 20:09:35 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_window2(t_game *game, int option)
{
	if (option == 0)
		perror("Error creating window");
	else
		perror("Error creating canvas window");
	clean_up_memory(game);
	exit (1);
}

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

void	render_static_background(t_game *game)
{
	int		x, y;
	float	factor;
	int		back_h;
	int		base_floor = 0x00664400;
	int		base_ceiling = 0x00664444;

	back_h = WIN_H + 2 * JUMPING;
	game->win->background.img = mlx_new_image(game->win->mlx, WIN_W, back_h);
	if (!game->win->background.img)
		error_window2(game, 1);
	game->win->background.addr = mlx_get_data_addr(game->win->background.img,
		&game->win->background.bits_x_pixel,
		&game->win->background.line_length,
		&game->win->background.endian);
	if (!game->win->background.addr)
		error_window2(game, 1);
	y = 0;
	while (y < back_h)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y < back_h / 2)
			{
				factor = 1.3f * (1.0f - (float)y / (back_h / 2));
				if (factor > 1.0f) factor = 1.0f;
				if (factor < 0.0f) factor = 0.0f;
				put_pixel(&game->win->background, x, y, darker_color(base_ceiling, factor));
			}
			else
			{
				factor = 1.3f * (1.0f - (float)(back_h - y) / (back_h / 2));
				if (factor > 1.0f) factor = 1.0f;
				if (factor < 0.0f) factor = 0.0f;
				put_pixel(&game->win->background, x, y, darker_color(base_floor, factor));
			}
			x++;
		}
		y++;
	}
}

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
		src = game->win->background.addr + 
			((y + offset_y) * game->win->background.line_length);
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
