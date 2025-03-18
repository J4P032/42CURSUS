/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:52:19 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/18 20:32:15 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	pacman_sprite_anim(t_window *win)
{
	static int		i;
	static int		j;
	int				time;

	time = 1;
	//mlx_put_image_to_window(win->mlx, win->win, win->canvas.img, 0, 0);
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
	if (!game->win->running)
		return (0);
	pacman_iddle(game);
	pre_movement(game);
	frame_collect(game);
	pacman_sprite_anim(game->win);

	delay_time(game);

	return (0);
}
