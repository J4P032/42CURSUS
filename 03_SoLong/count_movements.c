/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:25:51 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/20 18:17:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	where_is_pacman(t_game *game)
{
	game->win->sprite[0].prev_i = game->win->sprite[0].i;
	game->win->sprite[0].prev_j = game->win->sprite[0].j;
}

void	count_movements(t_game *game)
{
	if (game->win->sprite[0].i != game->win->sprite[0].prev_i)
	{
		game->win->sprite[0].distance++;
		ft_putnbr_fd(game->win->sprite[0].distance, 1);
		write(1, "\n", 1);
	}
	if (game->win->sprite[0].j != game->win->sprite[0].prev_j)
	{
		game->win->sprite[0].distance++;
		ft_putnbr_fd(game->win->sprite[0].distance, 1);
		write(1, "\n", 1);
	}
}
