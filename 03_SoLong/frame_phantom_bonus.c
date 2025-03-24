/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_phantom_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:49:08 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/24 21:55:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	reset_map(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	game->win->sprite[14].distance = 0;
	while (i < game->map->lines)
	{
		j = 0;
		while (j < game->map->columns)
		{
			if (game->map_cpy[i][j] == 'H' || game->map_cpy[i][j] == 'g')
				game->map_cpy[i][j] = '0';
			j++;
		}
		i++;
	}
}

/*game->win->sprite[14].go_down++ is counter to set speed of ghost*/
void	phantom_path_finding(t_game *game)
{
	int	i;
	int	j;
	int	x_offset;
	int	y_offset;

	i = game->win->sprite[14].y / SPRITE_HEIGHT;
	j = game->win->sprite[14].x / SPRITE_WIDTH;
	x_offset = game->win->sprite[14].x % SPRITE_WIDTH;
	y_offset = game->win->sprite[14].y % SPRITE_HEIGHT;
	if (y_offset != 0 && game->win->sprite[14].go_up == 'u')
		i = i + 1;
	if (x_offset != 0 && game->win->sprite[14].go_up == 'l')
		j = j + 1;
	if (game->map_cpy[i][j + 1] == '0' && x_offset == 0 && y_offset == 0)
		game->map_cpy[i][j + 1] = 'g';
	else if (game->map_cpy[i][j - 1] == '0' && x_offset == 0 && y_offset == 0)
		game->map_cpy[i][j - 1] = 'g';
	else if (game->map_cpy[i + 1][j] == '0' && x_offset == 0 && y_offset == 0)
		game->map_cpy[i + 1][j] = 'g';
	else if (game->map_cpy[i - 1][j] == '0' && x_offset == 0 && y_offset == 0)
		game->map_cpy[i - 1][j] = 'g';
	if (game->map_cpy[i][j] != '1')
		game->map_cpy[i][j] = 'H';
	game->win->sprite[14].distance++;
	game->win->sprite[14].go_down++;
}

/*win->sprite[14].go_down % 2 == 0 middle speed of pacman*/
void	phantom_move(t_game *g)
{
	int	x;
	int	y;

	x = g->win->sprite[14].j * SPRITE_WIDTH;
	y = g->win->sprite[14].i * SPRITE_HEIGHT;
	if (g->win->sprite[14].x != x && g->win->sprite[14].go_down % 2 == 0)
	{
		if (g->win->sprite[14].x < x)
			g->win->sprite[14].x++;
		else if (g->win->sprite[14].x > x)
		{
			g->win->sprite[14].go_up = 'l';
			g->win->sprite[14].x--;
		}
	}
	else if (g->win->sprite[14].y != y && g->win->sprite[14].go_down % 2 == 0)
	{
		if (g->win->sprite[14].y < y)
			g->win->sprite[14].y++;
		else if (g->win->sprite[14].y > y)
		{
			g->win->sprite[14].go_up = 'u';
			g->win->sprite[14].y--;
		}
	}
}

void	phantom_anim(t_game *game)
{
	int	flag;

	flag = 0;
	phantom_path_finding(game);
	if (!flag)
		phantom_go_up(game);
	else
		phantom_go_down(game);
	phantom_move(game);
	mlx_put_image_to_window(game->win->mlx, game->win->win,
		game->win->sprite[14].img[0].img, game->win->sprite[14].x,
		game->win->sprite[14].y);
	if ((game->win->sprite[14].distance > 1500
			|| game->win->sprite[0].distance % 8 == 0) && !flag)
	{
		flag = 1;
		reset_map(game);
	}
	if ((game->win->sprite[14].distance > 2000
			|| game->win->sprite[0].distance % 8 == 0) && flag)
	{
		flag = 0;
		reset_map(game);
	}
	/* for (size_t i = 0; i < game->map->lines; i++) //
	{
		printf("%s", game->map_cpy[i]);//
	}
	printf("\n");//
	printf ("i:%d\n", game->win->sprite[14].i); //
	printf ("j:%d\n", game->win->sprite[14].j); //
	printf ("x:%d\n", game->win->sprite[14].x); //
	printf ("y:%d\n", game->win->sprite[14].y); // */
}
