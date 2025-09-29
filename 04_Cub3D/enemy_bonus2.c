/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:44:09 by jrollon-          #+#    #+#             */
/*   Updated: 2025/09/29 19:35:05 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

void	enemy_invisible_behind_screen(t_game *game)
{
	if (game->enemy.screen_x + game->enemy.sprite_size < 0
		|| game->enemy.screen_x >= WIN_W
		|| game->enemy.screen_y + game->enemy.sprite_size < 0)
		game->enemy.visible = 0;
	else
		game->enemy.visible = 1;
}

/*just one enemy 'x' allowed, if more return 1, else 0*/
int	enemy_position(t_game *game, size_t x, size_t y)
{
	srand(time(NULL));
	while (y < game->map->lines)
	{
		x = 0;
		while (x < game->map->columns)
		{
			if (game->map->map[y][x] == 'x')
			{
				game->enemy.num_enemies++;
				if (game->enemy.num_enemies > 1)
					return (1);
				game->enemy.e_x = x + 0.5;
				game->enemy.e_y = y + 0.5;
				game->enemy.number_hits = 0;
				game->enemy.go_down = 0;
				game->enemy.time = 0;
			}
			x++;
		}
		y++;
	}
	return (0);
}

/*We want to transform the sprite vector in the world (e_dx, e_dy) to camera...
...coordinates (trans_x, trans_y), and that is a matrix formula:

⎡trans_x⎤ = M-¹ * ⎡e_dx⎤
⎣trans_y⎦	      ⎣e_dy⎦

M-¹ = 1 / det(M) ⎡plane_y  -plane_x⎤
                 ⎣-dir_y   -dir_x  ⎦

det(M) =  dir_x * plane_y - dir_y * plane_x 

inv_det = 1 / det(M)
but I change to det(M) = - dir_x * plane_y + dir_y * plane_x because invert
to make it appear in screen, because hidding behind wall corners.

if (trans_y <= 0.0) return; if sprite is behind camera don't calculate.

if (sprite_size > WIN_H * 2) sprite_size = WIN_H * 2; to not force high spend...
in performance.
Last return is to not glue the sprite when moving camera to border of screen.
if enemy is behind de camera then we don't draw it*/
void	calculate_screen_pos_size(t_game *game, double dx, double dy, int i)
{
	t_map	*map;
	double	inv_det;
	double	trans_x;
	double	trans_y;
	int		sprite_size;

	map = game->map;
	inv_det = 1.0 / (map->plane_x * map->dir_y - map->dir_x * map->plane_y);
	trans_x = inv_det * (map->dir_y * dx - map->dir_x * dy);
	trans_y = inv_det * (-map->plane_y * dx + map->plane_x * dy);
	if (trans_y <= 0.0)
	{
		game->enemy.visible = 0;
		return ;
	}
	sprite_size = (int)fabs(WIN_H / trans_y);
	if (sprite_size > WIN_H * 2)
		sprite_size = WIN_H * 2;
	game->enemy.sprite_size = sprite_size;
	game->enemy.screen_x = (int)((WIN_W / 2) * (1 + trans_x / trans_y))
		- game->enemy.sprite_size / 2 + cos(i) * game->enemy.sprite_size / 9.9f;
	game->enemy.screen_y = -game->enemy.sprite_size / 2 + WIN_H / 2
		+ game->win->ray.walking_height
		+ sin(i) * game->enemy.sprite_size / 20.0f;
	enemy_invisible_behind_screen(game);
}
