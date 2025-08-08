/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:59:10 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/08 10:25:15 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->map->lines)
	{
		free(game->map->map[i]);
		game->map->map[i] = NULL;
		i++;
	}
	free(game->map->map);
	free(game->map);
}

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

void	clean_up_memory(t_game *game, size_t i)
{
	while (i < NUM_SPRITES)
		free_sprites(&game->win->sprite[i++], game->win->mlx);
	if (game->win->canvas.img)
		mlx_destroy_image(game->win->mlx, game->win->canvas.img);
	if (game->win->bg.img)
		mlx_destroy_image(game->win->mlx, game->win->bg.img);
	if (game->win->buffer.img)
		mlx_destroy_image(game->win->mlx, game->win->buffer.img);
	if (game->win->win)
	{
		mlx_destroy_window(game->win->mlx, game->win->win);
		game->win->win = NULL;
	}
	if (game->win->mlx)
	{
		mlx_destroy_display(game->win->mlx);
		free(game->win->mlx);
		game->win->mlx = NULL;
	}
	if (game->win)
		free(game->win);
	if (game->map)
		free_map(game);
	free (game);
}

/*mlx_mouse_hide has leaks*/
//mlx_mouse_hide(game->win->mlx, game->win->win);
void	hooks(t_game *game)
{
	mlx_mouse_move(game->win->mlx, game->win->win, WIN_W / 2, WIN_H / 2);
	mlx_loop_hook(game->win->mlx, update_frame, game);
	mlx_hook(game->win->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win->win, MotionNotify, PointerMotionMask,
		mouse_rotation, game);
	mlx_hook(game->win->win, 17, 0, close_win, game);
	mlx_loop(game->win->mlx);
}

/*Could use t_window without pointer BUT 'cause errors in free I init all to 0*/
int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (1);
	(void)argc;
	//check_ber(argv[1]);
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		return (1);
	game->win = (t_window *)ft_calloc(1, sizeof(t_window));
	if (!game->win)
		return (free(game), 1);
	game->win->running = 1;
	game->win->mlx = mlx_init();
	if (!game->win->mlx)
		return (free(game->win), free(game), 1);
	game->map = process_map(argv[1]);
	if (!game->map)
		return (clean_up_memory(game, 0), 1);
	draw_window(game);
	load_sprites_and_background(game);
	hooks(game);
	return (0);
}
