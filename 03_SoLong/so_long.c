/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:09:02 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/04 20:13:43 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"
#include <math.h>
#include <stdlib.h>
#define WIDTH 1024
#define HEIGHT 1024

typedef struct s_data
{
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
	int		endian;
}           t_data;

int	close_win(void *param)
{
	(void)param;
	exit(0);
	return (0);
}


int main(void)
{
	void	*mlx;
	void	*mlx_win;
	int		x;
	int		y;
	int		color;

	//t_data	img;
	x = 50;
	y = 50;
	color = 0xff0000;
	mlx = mlx_init();
	if (!mlx)
		return (1);
	/* img.img = mlx_new_image(mlx, 1929, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
					&img.endian); */

	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "titulitis");
	if(!mlx_win)
		return (1);

	double k = 0;
	while (y < HEIGHT / 2)
	{
		x = 50;
		k = 0;
		color = 0xf00000;
		while (x < WIDTH)
		{
			mlx_pixel_put(mlx, mlx_win, x,  sin(k) + tan(k) * y, color);
			color += 0.0001 * 0x010000;
			x++;
			k = k + 0.001;
		}
		y++;
	}


	mlx_hook(mlx_win, 17, 0, close_win, mlx_win);
	mlx_loop(mlx);
}
