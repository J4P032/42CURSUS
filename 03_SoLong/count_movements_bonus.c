/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_movements_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:25:51 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/21 15:32:40 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	where_is_pacman(t_game *game)
{
	game->win->sprite[0].prev_i = game->win->sprite[0].i;
	game->win->sprite[0].prev_j = game->win->sprite[0].j;
}

void	count_movements(t_game *g)
{
	char	*number;
	int		x;
	int		y;

	x = g->win->width / 2;
	y = g->win->height - 64;
	number = NULL;
	if (g->win->sprite[0].i != g->win->sprite[0].prev_i
		|| g->win->sprite[0].j != g->win->sprite[0].prev_j)
	{
		g->win->sprite[0].distance++;
		number = ft_itoa(g->win->sprite[0].distance);
		mlx_put_image_to_window(g->win->mlx, g->win->win,
			g->win->sprite[8].img[0].img, x, y);
		mlx_string_put(g->win->mlx, g->win->win, x - 32, y + 39,
			0x00ff00, "Movements:");
		mlx_string_put(g->win->mlx, g->win->win, x + 32, y + 39,
			0xffff00, number);
		free(number);
	}
}
