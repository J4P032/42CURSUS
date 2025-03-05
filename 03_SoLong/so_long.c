/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:09:02 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/05 13:02:32 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_win(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

/*function that "push" pixels into the screen*/
/*we receive the data struct of the image created (a canvas)...*/
/*...and obtain the memory of start of it with img->addr that comes from...*/
/*...mlx_get_data_addr. BUT instead of address of x,y pixel = y * 1920 + x...*/
/*...ex: &(2,1)pixel =  1 * 1920 + 2 = 1922 "index" = 1922 x 4bytes/pixel... */
/*...each line of the 1080 lines it is not 1920 x 4 = 7680 bytes but more...*/
/*...because minilibx way of doing. Real number is img.line_length sooooo ...*/
/*...address(char to add 1byte) is &image + y * line_length + x * (...)'cause*/
/*...RGB are 3 bytes = 24bites, ARGB = 4 bytes = 32 bites so as each pixel...*/
/*...is 4bytes so 8 * 4 = 32bites bits_x_pixel = 32 or 24 / 8 gives bytes.*/
/**(unsigned int*)pxl_adr = color once we have the &mem, we assign value of..*/
/*...it with full red 0xff000000(RGBA). Minilibx don't allow alpha BUT...*/
/*...we can ignore it. We could use 24bits(RGB)but should assign each pixel..*/
/*...as: pxl_adr[0] = color & 0xFF //lowbyte blue*/
/*...pxl_adr[1] = (color >> 8) & 0xFF; //middle byte green */
/*...pxl_adr[2] = (color >> 16) & 0xFF; //higher byte red */
/*...we move >> the bytes to the lower value to modify them*/
void	put_pixel(t_data *img, int x, int y, int color)
{
	char	*pxl_adr;

	pxl_adr = img->addr + (y * img->line_length + x * (img->bits_x_pixel / 8));
	*(unsigned int*)pxl_adr = color;
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "So Long");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_x_pixel, &img.line_length,
					&img.endian);
	put_pixel(&img, WIDTH / 2, HEIGHT / 2, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(mlx_win, 17, 0, close_win, mlx_win);
	mlx_loop(mlx);
}
