/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_phantom2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:06:23 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/24 21:55:02 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	phantom_go_up(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < game->map->lines)
	{
		j = 0;
		while (j < game->map->columns)
		{
			if (game->map_cpy[i][j] == 'g')
			{
				game->win->sprite[14].i = i;
				game->win->sprite[14].j = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	phantom_go_down(t_game *game)
{
	size_t	i;
	size_t	j;

	i = game->map->lines - 2;
	while (i > 0)
	{
		j = game->map->columns - 2;
		while (j > 0)
		{
			if (game->map_cpy[i][j] == 'g')
			{
				game->win->sprite[14].i = i;
				game->win->sprite[14].j = j;
				return ;
			}
			j--;
		}
		i--;
	}
}


/////////////////////////////////////////////////////

void	phantom2_go_up(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < game->map->lines)
	{
		j = 0;
		while (j < game->map->columns)
		{
			if (game->map_cpy[i][j] == 'b')
			{
				game->win->sprite[15].i = i;
				game->win->sprite[15].j = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	phantom2_go_down(t_game *game)
{
	size_t	i;
	size_t	j;

	i = game->map->lines - 2;
	while (i > 0)
	{
		j = game->map->columns - 2;
		while (j > 0)
		{
			if (game->map_cpy[i][j] == 'b')
			{
				game->win->sprite[15].i = i;
				game->win->sprite[15].j = j;
				return ;
			}
			j--;
		}
		i--;
	}
}



void	reset2_map(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	game->win->sprite[15].distance = 0;
	while (i < game->map->lines)
	{
		j = 0;
		while (j < game->map->columns)
		{
			if (game->map_cpy[i][j] == 'J' || game->map_cpy[i][j] == 'b')
				game->map_cpy[i][j] = '0';
			j++;
		}
		i++;
	}
}

/*game->win->sprite[14].go_down++ is counter to set speed of ghost*/
void	phantom2_path_finding(t_game *game)
{
	int	i;
	int	j;
	int	x_offset;
	int	y_offset;

	i = game->win->sprite[15].y / SPRITE_HEIGHT;
	j = game->win->sprite[15].x / SPRITE_WIDTH;
	x_offset = game->win->sprite[15].x % SPRITE_WIDTH;
	y_offset = game->win->sprite[15].y % SPRITE_HEIGHT;
	if (y_offset != 0 && game->win->sprite[15].go_up == 'u')
		i = i + 1;
	if (x_offset != 0 && game->win->sprite[15].go_up == 'l')
		j = j + 1;
	if (game->map_cpy[i][j + 1] == '0' && x_offset == 0 && y_offset == 0)
		game->map_cpy[i][j + 1] = 'b';
	else if (game->map_cpy[i][j - 1] == '0' && x_offset == 0 && y_offset == 0)
		game->map_cpy[i][j - 1] = 'b';
	else if (game->map_cpy[i + 1][j] == '0' && x_offset == 0 && y_offset == 0)
		game->map_cpy[i + 1][j] = 'b';
	else if (game->map_cpy[i - 1][j] == '0' && x_offset == 0 && y_offset == 0)
		game->map_cpy[i - 1][j] = 'b';
	if (game->map_cpy[i][j] != '1')
		game->map_cpy[i][j] = 'J';
	game->win->sprite[15].distance++;
	game->win->sprite[15].go_down++;
}

/*win->sprite[14].go_down % 2 == 0 middle speed of pacman*/
void	phantom2_move(t_game *g)
{
	int	x;
	int	y;

	x = g->win->sprite[15].j * SPRITE_WIDTH;
	y = g->win->sprite[15].i * SPRITE_HEIGHT;
	if (g->win->sprite[15].x != x && g->win->sprite[15].go_down % 2 == 0)
	{
		if (g->win->sprite[15].x < x)
			g->win->sprite[15].x++;
		else if (g->win->sprite[15].x > x)
		{
			g->win->sprite[15].go_up = 'l';
			g->win->sprite[15].x--;
		}
	}
	else if (g->win->sprite[15].y != y && g->win->sprite[15].go_down % 2 == 0)
	{
		if (g->win->sprite[15].y < y)
			g->win->sprite[15].y++;
		else if (g->win->sprite[15].y > y)
		{
			g->win->sprite[15].go_up = 'u';
			g->win->sprite[15].y--;
		}
	}
}

void	phantom2_anim(t_game *game)
{
	int	flag;

	flag = 0;
	phantom2_path_finding(game);
	if (!flag)
		phantom2_go_up(game);
	else
		phantom2_go_down(game);
	phantom2_move(game);
	mlx_put_image_to_window(game->win->mlx, game->win->win,
		game->win->sprite[15].img[0].img, game->win->sprite[15].x,
		game->win->sprite[15].y);
	if ((game->win->sprite[15].distance > 1500
			|| game->win->sprite[0].distance % 8 == 0) && !flag)
	{
		flag = 1;
		reset2_map(game);
	}
	if ((game->win->sprite[15].distance > 2000
			|| game->win->sprite[0].distance % 8 == 0) && flag)
	{
		flag = 0;
		reset2_map(game);
	}
}
