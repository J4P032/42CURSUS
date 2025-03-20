/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_geometry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:26:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/20 18:22:46 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_square(t_data *canvas, int x, int y, int color)
{
	int	x2;
	int	y2;

	x2 = x;
	y2 = y;
	while (y2 < y + 32)
	{
		x2 = x;
		while (x2 < x + 32)
		{
			put_pixel(canvas, x2, y2, color);
			x2++;
		}
		y2++;
	}
}

void	draw_circle(t_data *canvas, int x, int y, int r, int color)
{
	int	x2;
	int	y2;

	y2 = y - r;
	while (y2 <= y + r)
	{
		x2 = x - r;
		while (x2 <= x + r)
		{
			if ((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y) <= r * r)
				put_pixel(canvas, x2, y2, color);
			x2++;
		}
		y2++;
	}
}
