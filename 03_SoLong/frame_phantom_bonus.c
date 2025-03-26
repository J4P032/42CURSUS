/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_phantom_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:49:08 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/25 13:16:43 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ghost_horizontal_movement(t_game *game, int n)
{
	int	wall_x;

	wall_x = next_wall_hor2(game, n);
	if (game->win->sprite[n].go_up == 'r')
	{
		if (game->win->sprite[n].x + SPRITE_WIDTH >= wall_x)
			game->win->sprite[n].x = wall_x - SPRITE_WIDTH;
		else
			(game->win->sprite[n].x)++;
	}
	else if (game->win->sprite[n].go_up == 'l')
	{
		if (game->win->sprite[n].x <= wall_x)
			game->win->sprite[n].x = wall_x;
		else
			(game->win->sprite[n].x)--;
	}
}

void	reset_map(t_game *game, int n, char g, char h)
{
	size_t	i;
	size_t	j;

	i = 0;
	game->win->sprite[n].distance = 0;
	while (i < game->map->lines)
	{
		j = 0;
		while (j < game->map->columns)
		{
			if (game->map_cpy[i][j] == h || game->map_cpy[i][j] == g)
				game->map_cpy[i][j] = '0';
			j++;
		}
		i++;
	}
}

/*game->win->sprite[n].go_down++ reused as is counter to set speed of ghost*/
void	phantom_path_finding(t_game *game, int n, char g, char h)
{
	int	i;
	int	j;
	int	x_offset;
	int	y_offset;

	i = game->win->sprite[n].y / SPRITE_HEIGHT;
	j = game->win->sprite[n].x / SPRITE_WIDTH;
	x_offset = game->win->sprite[n].x % SPRITE_WIDTH;
	y_offset = game->win->sprite[n].y % SPRITE_HEIGHT;
	if (y_offset != 0 && game->win->sprite[n].go_up == 'u')
		i = i + 1;
	if (x_offset != 0 && game->win->sprite[n].go_up == 'l')
		j = j + 1;
	if (game->map_cpy[i][j + 1] == '0' && x_offset == 0 && y_offset == 0)
		game->map_cpy[i][j + 1] = g;
	else if (game->map_cpy[i][j - 1] == '0' && x_offset == 0 && y_offset == 0)
		game->map_cpy[i][j - 1] = g;
	else if (game->map_cpy[i + 1][j] == '0' && x_offset == 0 && y_offset == 0)
		game->map_cpy[i + 1][j] = g;
	else if (game->map_cpy[i - 1][j] == '0' && x_offset == 0 && y_offset == 0)
		game->map_cpy[i - 1][j] = g;
	if (game->map_cpy[i][j] != '1')
		game->map_cpy[i][j] = h;
	game->win->sprite[n].distance++;
	game->win->sprite[n].go_down++;
}

/*win->sprite[n].go_down % 2 == 0 middle speed of pacman*/
void	phantom_move(t_game *g, int n)
{
	int	x;
	int	y;

	x = g->win->sprite[n].j * SPRITE_WIDTH;
	y = g->win->sprite[n].i * SPRITE_HEIGHT;
	if (g->win->sprite[n].x != x && g->win->sprite[n].go_down % 2 == 0)
	{
		if (g->win->sprite[n].x < x)
			g->win->sprite[n].go_up = 'r';
		else if (g->win->sprite[14].x > x)
			g->win->sprite[n].go_up = 'l';
		ghost_horizontal_movement(g, n);
	}
	else if (g->win->sprite[n].y != y && g->win->sprite[n].go_down % 2 == 0)
	{
		if (g->win->sprite[n].y < y)
			g->win->sprite[n].go_up = 'd';
		else if (g->win->sprite[n].y > y)
			g->win->sprite[n].go_up = 'u';
		ghost_vertical_movement(g, n);
	}
}

void	phantom_anim(t_game *game, int n, char g, char h)
{
	int	flag;

	flag = 0;
	phantom_path_finding(game, n, g, h);
	if (!flag)
		phantom_go_up(game, n, g);
	else
		phantom_go_down(game, n, g);
	phantom_move(game, n);
	mlx_put_image_to_window(game->win->mlx, game->win->win,
		game->win->sprite[n].img[0].img, game->win->sprite[n].x,
		game->win->sprite[n].y);
	if ((game->win->sprite[n].distance > 1500
			|| game->win->sprite[0].distance % 8 == 0) && !flag)
	{
		flag = 1;
		reset_map(game, n, g, h);
	}
}
