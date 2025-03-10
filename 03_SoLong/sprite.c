/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:04:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/10 22:53:39 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* int get_pixel_color(t_data *img, int x, int y) {
    char    *pixel;
    int     color;

    pixel = img->addr + (y * img->line_length + x * (img->bits_x_pixel / 8));

    if (img->bits_x_pixel == 32) {
        color = *(int *)pixel;
    } else if (img->bits_x_pixel == 24) {
        // Lee cada byte (R, G, B) y compón el color en formato 0x00RRGGBB
        color = (*(unsigned char *)(pixel + 2) << 16) |  // Red
                (*(unsigned char *)(pixel + 1) << 8)  |  // Green
                (*(unsigned char *)(pixel + 0));         // Blue
    } else {
        // Maneja otros formatos si es necesario
        color = 0x000000;
    }
    return (color);
}

void put_pixel_sprite(t_data *img, int x, int y, int color) {
    char    *pixel;

    pixel = img->addr + (y * img->line_length + x * (img->bits_x_pixel / 8));

    if (img->bits_x_pixel == 32) {
        *(int *)pixel = color;
    } else if (img->bits_x_pixel == 24) {
        // Erite cada componente (asume color en formato 0x00RRGGBB)
        *(unsigned char *)(pixel + 2) = (color >> 16) & 0xFF; // Red
        *(unsigned char *)(pixel + 1) = (color >> 8)  & 0xFF; // Green
        *(unsigned char *)(pixel + 0) = color         & 0xFF; // Blue
    }
} */













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

void	draw_transparent_sprite(t_window *win)
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
                put_pixel_sprite(&win->canvas, x, y, color);
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
