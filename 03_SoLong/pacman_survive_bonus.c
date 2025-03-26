/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pacman_survive_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:37:12 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/25 13:17:56 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	pacman_survive(t_game *game, int i_g, int j_g, int i_r)
{
	int	i;
	int	j;
	int	j_r;
	int	i_b;
	int	j_b;

	i = game->win->sprite[0].i;
	j = game->win->sprite[0].j;
	j_r = game->win->sprite[15].x / SPRITE_WIDTH;
	i_b = game->win->sprite[16].y / SPRITE_WIDTH;
	j_b = game->win->sprite[16].x / SPRITE_WIDTH;
	if ((i == i_g && j == j_g) || (i == i_r && j == j_r)
		|| (i == i_b && j == j_b))
	{
		clean_up_memory(game);
		exit (1);
	}
}
