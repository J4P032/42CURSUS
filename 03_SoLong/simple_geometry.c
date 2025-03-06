/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_geometry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:26:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/06 13:26:52 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_square(t_data *canvas, int x, int y, int color)
{

	int	x2;
	int	y2;

	x2 = x;
	y2 = y;
 	while (y2 < y + 16)
	{
		x2 = x;
		while (x2 < x + 16)
		{
			put_pixel(canvas, x2, y2, color);
			x2++;
		}
		y2++;
	}
}
