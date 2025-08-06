/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:11:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/06 16:37:47 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*function that "push" pixels into the image*/
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
	*(unsigned int *)pxl_adr = color;
}
