/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:04:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/11 09:28:40 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_pixel_color(t_data *img, int x, int y)
{
	char	*pixel;
	pixel = img->addr + (y * img->line_length + x * (img->bits_x_pixel / 8));
	return (*(int *)pixel);
}

void	put_pixel_sprite(t_data *img, int x, int y, int color)
{
	char	*pixel;
	pixel = img->addr + (y * img->line_length + x * (img->bits_x_pixel / 8));
	*(int *)pixel = color;
}

void	erase_transparent_sprite(t_window *win, int x2, int y2)
{
	int	x;
	int	y;

	y = 0;
	while (y < win->sprite.height)
	{
		x = 0;
		while (x < win->sprite.width)
		{
            put_pixel_sprite(&win->canvas, x + x2, y + y2, 0x000000);
			x++;
		}
		y++;
	}
}


void	draw_transparent_sprite(t_window *win, int x2, int y2)
{
	int	x;
	int	y;
	int	color;
	int	x_color;

	x_color = 0xF54892;
	y = 0;
	while (y < win->sprite.height)
	{
		x = 0;
		while (x < win->sprite.width)
		{
			color = get_pixel_color(&win->sprite.img, x, y);
			if ((color & 0x00FFFFFF) != x_color)
                put_pixel_sprite(&win->canvas, x + x2, y + y2, color);
			//if (color != x_color)
				//put_pixel_sprite(&win->sprite.img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_sprite(t_window *win)
{
	win->sprite.bitmap = "/home/jrollon-/Desktop/CURSUS/03_SoLong/fatasma.xpm";
	win->sprite.width = 64;
	win->sprite.height = 64;
	win->sprite.x = WIDTH / 4;
	win->sprite.y = HEIGHT / 4;
	//win->sprite.img.img = mlx_new_image(win->mlx, 64, 64);//
	win->sprite.img.img = mlx_xpm_file_to_image(win->mlx, win->sprite.bitmap,
			&win->sprite.width, &win->sprite.height);
	win->sprite.img.addr = mlx_get_data_addr(win->sprite.img.img,
			&win->sprite.img.bits_x_pixel,
			&win->sprite.img.line_length,
			&win->sprite.img.endian);
}
