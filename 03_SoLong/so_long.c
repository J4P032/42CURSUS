/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:09:02 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/13 17:35:39 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_sprites(t_sprite *sprite, void *mlx)
{
	size_t	i;

	i = 0;
	while (i < SPRITES_ANIM)
	{
		if (sprite->img[i].img)
			mlx_destroy_image(mlx, sprite->img[i].img);
		i++;
	}
}

void	clean_up_memory(t_window *win)
{
	size_t	i;

	i = 0;
	while (i < NUM_SPRITES)
		free_sprites(&win->sprite[i++], win->mlx);
	if(win->canvas.img)
		mlx_destroy_image(win->mlx, win->canvas.img);
	if (win->buffer.img)
		mlx_destroy_image(win->mlx, win->buffer.img);
	if (win->win)
	{
		mlx_destroy_window(win->mlx, win->win);
        win->win = NULL;
	}
	if (win->mlx)
	{
		mlx_destroy_display(win->mlx);
		free(win->mlx);
		win->mlx = NULL;
	}
	if (win)
		free(win);
}



int main(int argc, char **argv)
{
	t_window	*win; // = {0};
	//t_map		*map;

	if (argc != 2)
		return (1);
	win = (t_window *)ft_calloc(1, sizeof(t_window));
	if (!win)
		return (1);
	//win.win = NULL;
	win->running = 1;
	win->mlx = mlx_init();
	if (!win->mlx)
		return (free(win), 1);
	//map = process_map(argv[1]);
	(void)argv;
	/* if (!map)
		return (1); */
	draw_window(win);
	load_pacman(win);
	mlx_loop_hook(win->mlx, update_frame, win);
	mlx_key_hook(win->win, key_press, win);
	////mlx_hook(win.win, 2, 1L<<0 | 1L<<1, print_msg, &win);
	mlx_hook(win->win, 17, 0, close_win, win);
	mlx_loop(win->mlx);
	//free(map);
	clean_up_memory(win);
	return (0);
}
