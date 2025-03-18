/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_collect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:28:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/18 20:03:52 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	pacman_eat(t_game *game)
{
	int	i;
	int	j;
	//int k;
	//int	l;

	//k = 0;
	//l = 0;
	i = game->win->sprite[0].y / SPRITE_HEIGHT;
	j = game->win->sprite[0].x / SPRITE_WIDTH;
	if (game->map->map[i][j] == 'C')
	{
		game->map->num_c--;
		game->map->map[i][j] = 'D';
		printf("%d\n", game->map->num_c); //
	/* 	while (k < 3)
		{
			mlx_put_image_to_window(game->win->mlx, game->win->win,
				game->win->sprite[12].img[k].img,
				game->win->sprite[0].x,
				game->win->sprite[0].y);
			l++;
			k = only_once(&l, 2);
		} */
	}
}

void	collect_sprite_anim(t_game *game, int x, int y)
{
	static int		i;
	static int		j;
	int				time;

	time = game->map->num_c;
	mlx_put_image_to_window(game->win->mlx, game->win->win,
		game->win->sprite[11].img[i].img, x, y);
	j++;
	i = scale_time(&j, time);
}


void	collect_sprite_anim2(t_game *game, int x, int y)
{
	static int		i;
	static int		j;
	int				time;

	time = 4;
	mlx_put_image_to_window(game->win->mlx, game->win->win,
		game->win->sprite[12].img[i].img, x, y);
	j++;
	i = only_once(&j, time);
	if (i == 2)
	{
		game->map->map[y / SPRITE_HEIGHT][x / SPRITE_WIDTH] = '0';
		i = 0;
	}
}

void	frame_collect(t_game *game)
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
			if (game->map->map[i][j] == 'C')
				collect_sprite_anim(game, x, y);
			if (game->map->map[i][j] == 'D')
				collect_sprite_anim2(game, x, y);
			j++;
		}
		i++;
	}
	pacman_eat(game);
}
