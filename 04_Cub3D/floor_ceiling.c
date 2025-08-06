/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:57:50 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/06 12:31:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_window2(t_game *game, int option)
{
	if (option == 0)
		perror("Error creating window");
	else
		perror("Error creating background window");
	clean_up_memory(game);
	exit (1);
}

/*imagine a color like pure Yellow 0x00FFFF00 that is RED(255) + GREEN (255)
to brighter or darker the color we have to multiply per same factor all color
channels, so R, G and B by same factor. To extract the channels of the color:
YELLOW is 0x00FFFF00 = 00000000 11111111 11111111 00000000 
1.RED is the second of the left 8bits group, we want to only have the RED so:
	color >> 16 -> 00000000 00000000 00000000 11111111
	& 0xFF (00000000 00000000 00000000 11111111) = 0xFF (the same) = 255
	if we want to dark it (multiply per 0.5) = 255 / 2 = 127.5 
	127(we pick the int part) = 0111 1111. That is the RED darked
2.GREEN channel will be same 127 as we >> 8 only
3.BLUE will be 0 as color final 8 bits are 00000000
The compose the full color will be:
RED 00000000 01111111 00000000 00000000
GRE 00000000 00000000 01111111 00000000
BLU 00000000 00000000 00000000 00000000
Sol 00000000 01111111 01111111 00000000 that is 0x007F7F00 yellow darker.*/
int	gradient(int color, float factor)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	color = (r << 16) | (g << 8) | b;
	return (color);
}

/*
n is the factor that will multiply the color to obtain darker one and a...
gradient in all of it so in each middle n will be 1.0 to 0.0 in ceiling from...
...top to botton and from 0.0 to 1.0 in floor with each 'y'. 1.3f is brightness
multiplier.*/
void	paint_sky_floor(t_game *game, int x, int y, int back_h)
{
	float	n;

	while (x < WIN_W)
	{
		if (y < back_h / 2)
		{
			n = 1.3f * (1.0f - (float)y / (back_h / 2));
			if (n > 1.0f)
				n = 1.0f;
			if (n < 0.0f)
				n = 0.0f;
			put_pixel(&WIN->background, x, y, gradient(MAP->sky_color, n));
		}
		else
		{
			n = 1.3f * (1.0f - (float)(back_h - y) / (back_h / 2));
			if (n > 1.0f)
				n = 1.0f;
			if (n < 0.0f)
				n = 0.0f;
			put_pixel(&WIN->background, x, y, gradient(MAP->floor_color, n));
		}
		x++;
	}
}

/*background ceiling and floor will be same WIDTH as the screen, BUT...
will be JUMPING pixels up and down to allow PAN of it when jumping
so better performance instead of render pixels each frame*/
void	render_jumping_background(t_game *game)
{
	int		y;
	int		back_h;

	MAP->floor_color = 0x00664400;
	MAP->sky_color = 0x00664444;
	back_h = WIN_H + 2 * JUMPING;
	WIN->background.img = mlx_new_image(WIN->mlx, WIN_W, back_h);
	if (!WIN->background.img)
		error_window2(game, 1);
	WIN->background.addr = mlx_get_data_addr(WIN->background.img,
			&WIN->background.bits_x_pixel, &WIN->background.line_length,
			&WIN->background.endian);
	if (!WIN->background.addr)
		error_window2(game, 1);
	y = 0;
	while (y < back_h)
	{
		paint_sky_floor(game, 0, y, back_h);
		y++;
	}
}

