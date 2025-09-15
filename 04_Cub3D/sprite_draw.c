/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:56:38 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/15 13:30:19 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_enemy_on_canvas(t_game *game, t_sprite sprite, int px, int py)
{
    int i, j, color, tex_x, tex_y;
    char *src;
    int tex_w = TEXTURE_W;
    int tex_h = TEXTURE_H;
    int start_i = 0;
    int end_i = game->enemy.sprite_size;
    int start_j = 0;
    int end_j = game->enemy.sprite_size;

    /* calcular rango visible en X */
    if (px < 0)
        start_i = -px; /* saltar columnas a la izquierda */
    if (px + game->enemy.sprite_size > WIN_W)
        end_i = WIN_W - px; /* cortar por la derecha */

    /* calcular rango visible en Y */
    if (py < 0)
        start_j = -py;
    if (py + game->enemy.sprite_size > WIN_H)
        end_j = WIN_H - py;

    for (j = start_j; j < end_j; ++j)
    {
        for (i = start_i; i < end_i; ++i)
        {
            tex_x = (i * tex_w) / game->enemy.sprite_size;
            tex_y = (j * tex_h) / game->enemy.sprite_size;
            src = sprite.img[0].addr + (tex_y * sprite.img[0].line_length + tex_x * (sprite.img[0].bits_x_pixel / 8));
            color = *(unsigned int *)src;
            if (color != 0x00F8FF00)
                put_pixel(&game->win->canvas, px + i, py + j, color);
        }
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
