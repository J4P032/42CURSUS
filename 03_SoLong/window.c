/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:12:33 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/05 14:24:25 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_win(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	draw_window(void *mlx, void **window, t_data *image)
{
	if (!*window)
		*window = mlx_new_window(mlx, WIDTH, HEIGHT, "So Long");
	image->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	image->addr = mlx_get_data_addr(image->img, &(image)->bits_x_pixel,
			&(image)->line_length, &(image)->endian);
}
