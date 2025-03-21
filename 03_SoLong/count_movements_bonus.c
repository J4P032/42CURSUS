/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_movements_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:25:51 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/21 14:09:29 by jrollon-         ###   ########.fr       */
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
	char	*number;
	int		x;
	int		y;

	x = game->win->width / 2;
	y = game->win->height - 32;
	number = NULL;
	if (game->win->sprite[0].i != game->win->sprite[0].prev_i)
	{
		game->win->sprite[0].distance++;
		number = ft_itoa(game->win->sprite[0].distance);
		mlx_string_put(game->win->mlx, game->win->win, x, y , 0xffffff, "Moves:");
		//mlx_clear_window(game->win->mlx, game->win->win);
		mlx_string_put(game->win->mlx, game->win->win, x + 64, y , 0xffffff, number);
		free(number);
	}
	if (game->win->sprite[0].j != game->win->sprite[0].prev_j)
	{
		game->win->sprite[0].distance++;
		number = ft_itoa(game->win->sprite[0].distance);
		mlx_string_put(game->win->mlx, game->win->win, x, y, 0xFFFFFF, "Moves: ");
		//mlx_clear_window(game->win->mlx, game->win->win);
		mlx_string_put(game->win->mlx, game->win->win, x + 64, y , 0xffffff, number);
		free(number);
	}
}
