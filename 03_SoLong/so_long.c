/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:09:02 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/15 20:17:04 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	clean_up_memory(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < NUM_SPRITES)
		free_sprites(&game->win->sprite[i++], game->win->mlx);
	if(game->win->canvas.img)
		mlx_destroy_image(game->win->mlx, game->win->canvas.img);
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

/*Could use t_window without pointer BUT 'cause errors in free I init all to 0*/
int main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (1);
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
		return (clean_up_memory(game), 1);
	draw_window(game);
	load_sprites(game);
	mlx_loop_hook(game->win->mlx, update_frame, game);
	mlx_key_hook(game->win->win, key_press, game);
	mlx_hook(game->win->win, 17, 0, close_win, game);
	mlx_loop(game->win->mlx);
	//clean_up_memory(game);  //sale antes de llegar aqui.. y lo limpia bien.
	return (0);
}
