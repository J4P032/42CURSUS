/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:56:38 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/10 20:06:30 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_enemy_on_canvas(t_game *game, t_sprite sprite, int px, int py)
{
	int		i;
	int		j;
	int		color;
	int		tex_x;
	int		tex_y;
	char	*src;

	// Obtener las dimensiones de la textura (asumiendo que todas las imágenes del sprite tienen el mismo tamaño)
	int tex_width = TEXTURE_W;
	int tex_height = TEXTURE_H;

	j = 0;
	while (j < game->enemy.sprite_size)
	{
		i = 0;
		while (i < game->enemy.sprite_size)
		{
			// Calcular la coordenada de textura correspondiente
			tex_x = (i * tex_width) / game->enemy.sprite_size;
			tex_y = (j * tex_height) / game->enemy.sprite_size;

			// Asegurarse de que las coordenadas de textura estén dentro de los límites
			if (tex_x >= 0 && tex_x < tex_width && tex_y >= 0 && tex_y < tex_height)
			{
				src = sprite.img[0].addr + (tex_y * sprite.img[0].line_length + tex_x * (sprite.img[0].bits_x_pixel / 8));
				color = *(unsigned int *)src;
				// Solo dibujar si el color no es el color clave (0x00F8FF00) y está dentro de la pantalla
				if (color != 0x00F8FF00 && px + i >= 0 && px + i < WIN_W && py + j >= 0 && py + j < WIN_H)
					put_pixel(&game->win->canvas, px + i, py + j, color);
			}
			i++;
		}
		j++;
	}
}








void	draw_minisprite_on_canvas(t_game *game, t_sprite sprite, int x, int y)
{
	size_t	i;
	size_t	j;
	int		color;
	char	*src;

	j = 0;
	while (j < MINISPRITE)
	{
		i = 0;
		while (i < MINISPRITE)
		{
			src = sprite.img[0].addr + (j * sprite.img[0].line_length
					+ i * (sprite.img[0].bits_x_pixel / 8));
			color = *(unsigned int *)src;
			put_pixel(&game->win->canvas, x + i, y + j, color);
			i++;
		}
		j++;
	}
}
