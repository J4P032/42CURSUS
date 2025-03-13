/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:09:02 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/13 12:42:33 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_error()
{
	return;
}

int main(int argc, char **argv)
{
	t_window	win;
	t_map		*map;

	win.win = NULL;
	if (argc != 2)
		return (1);
	map = process_map(argv[1]);
	if (!map)
		return (print_error(), 1); //si no es error salir por que sera que map = NULL
	win.mlx = mlx_init();
	draw_window(&win);
	load_pacman(&win);
	win.x = WIDTH / 2;
	win.angle = 0;
	win.running = 1;
	mlx_loop_hook(win.mlx, update_frame, &win);
	mlx_key_hook(win.win, key_press, &win);
	//mlx_hook(win.win, 2, 1L<<0 | 1L<<1, print_msg, &win);
	mlx_hook(win.win, 17, 0, close_win, &win);
	mlx_loop(win.mlx);
	return (0);
}
