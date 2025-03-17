/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:52:19 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/17 15:56:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	scale_time(int *num)
{
	if (*num < 100)
		return (1);
	if (*num > 200 && *num < 300)
		return (2);
	if (*num == 300)
	{
		*num = 0;
		return (0);
	}
	return (0);
}

void	pacman_sprite_anim(t_window *win)
{
	static int		i;
	static int		j;

	mlx_put_image_to_window(win->mlx, win->win, win->canvas.img, 0, 0);
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
	i = scale_time(&j);
}

int	update_frame(t_game *game)
{
	if (!game->win->running)
		return (0);
	pacman_iddle(game);
	//frame_map(game); //aqui permitiria que fuera lento pero sin pixeles. comentar la linea de mlx_put_image_to_window de arriba
	pre_movement(game);
	pacman_sprite_anim(game->win);
	return (0);
}
