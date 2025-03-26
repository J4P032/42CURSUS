/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:46:57 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/25 13:07:24 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	pacman_sprite_anim(t_window *win)
{
	static int		i;
	static int		j;
	int				time;

	time = 1;
	if (win->sprite->go_right)
		mlx_put_image_to_window(win->mlx, win->win, win->sprite[0].img[i].img,
			win->sprite[0].x, win->sprite[0].y);
	if (win->sprite->go_left)
		mlx_put_image_to_window(win->mlx, win->win, win->sprite[1].img[i].img,
			win->sprite[0].x, win->sprite[0].y);
	if (win->sprite->go_up)
		mlx_put_image_to_window(win->mlx, win->win, win->sprite[2].img[i].img,
			win->sprite[0].x, win->sprite[0].y);
	if (win->sprite->go_down)
		mlx_put_image_to_window(win->mlx, win->win, win->sprite[3].img[i].img,
			win->sprite[0].x, win->sprite[0].y);
	if (win->sprite->go_right != 0 || win->sprite->go_left != 0
		|| win->sprite->go_up != 0 || win->sprite->go_down != 0)
		j++;
	i = scale_time(&j, time);
}

int	update_frame(t_game *game)
{
	const double	time = 0.03;

	where_is_pacman(game);
	pacman_iddle(game);
	pre_movement(game);
	frame_collect(game);
	frame_exit(game);
	pacman_sprite_anim(game->win);
	if (game->map->num_g == 3)
	{
		phantom_anim(game, 14, 'g', 'H');
		phantom_anim(game, 15, 'r', 'J');
		phantom_anim(game, 16, 'b', 'K');
		pacman_survive(game, game->win->sprite[14].y / SPRITE_HEIGHT,
			game->win->sprite[14].x / SPRITE_WIDTH,
			game->win->sprite[15].y / SPRITE_HEIGHT);
	}
	delay_time(game, time);
	count_movements(game);
	return (0);
}
