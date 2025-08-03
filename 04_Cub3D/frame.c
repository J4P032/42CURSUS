/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:01:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/03 15:43:27 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	pacman_sprite_anim(t_window *win)
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
} */

/*We send a ray per pixel in width of the screen*/
int	update_frame(t_game *game)
{
	//const double	time = 0.03;
	int				x;

	x = 0;
	while (x < game->win->width)
		raycaster(game, x++);




	
	//where_is_pacman(game);
	//pacman_iddle(game);
	//pre_movement(game);
	//frame_collect(game);
	//frame_exit(game);
	//pacman_sprite_anim(game->win);
	//delay_time(game, time);
	//count_movements(game);
	return (0);
}
