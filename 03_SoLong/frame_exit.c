/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:49:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/19 13:16:59 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_sprite_anim(t_game *game, int x, int y)
{
	int	i;
	int	num_c;

	i = 0;
	num_c = game->map->num_c;
	if (num_c > 0 && num_c < 10)
		i = 1;
	if (num_c == 0)
		i = 2;
	if (game->map)
	mlx_put_image_to_window(game->win->mlx, game->win->win,
		game->win->sprite[13].img[i].img, x, y);
}

void	frame_exit(t_game *game)
{
	size_t	i;
	size_t	j;
	int		x;
	int		y;

	i = 0;
	while (i < game->map->lines)
	{
		j = 0;
		while (j < game->map->columns)
		{
			x = SPRITE_WIDTH * j;
			y = SPRITE_HEIGHT * i;
			if (game->map->map[i][j] == 'E')
				exit_sprite_anim(game, x, y);
			j++;
		}
		i++;
	}
	pacman_eat(game);

}
