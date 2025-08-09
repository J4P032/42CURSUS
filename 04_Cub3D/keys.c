/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 09:45:55 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/09 14:02:09 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	menu_keys(int key, t_game *game)
{
	if (key == XK_Escape)
	{
		clean_up_memory(game, 0);
		exit (0);
	}
	if (key == 'm' || key == 'M')
		game->keys.m = 1;
}

void	menu_keys_release(int key, t_game *game)
{
	if (key == 'm' || key == 'M')
		game->keys.m = 0;
}

int	key_press(int key, t_game *game)
{
	game->player.moving = 1;
	if (key == 'D' || key == 'd')
		game->keys.d = 1;
	if (key == 'A' || key == 'a')
		game->keys.a = 1;
	if (key == 'W' || key == 'w')
		game->keys.w = 1;
	if (key == 'S' || key == 's')
		game->keys.s = 1;
	if (key == XK_Right)
		game->keys.right = 1;
	if (key == XK_Left)
		game->keys.left = 1;
	if (key == XK_space)
		game->keys.space = 1;
	if (key == XK_Shift_L)
		game->keys.shift = 1;
	menu_keys(key, game);
	return (0);
}

/*key 65307 is ESC key*/
int	key_release(int key, t_game *game)
{
	if (key == 'D' || key == 'd')
		game->keys.d = 0;
	if (key == 'A' || key == 'a')
		game->keys.a = 0;
	if (key == 'W' || key == 'w')
		game->keys.w = 0;
	if (key == 'S' || key == 's')
		game->keys.s = 0;
	if (key == XK_Right)
		game->keys.right = 0;
	if (key == XK_Left)
		game->keys.left = 0;
	if (key == XK_space)
		game->keys.space = 0;
	if (key == XK_Shift_L)
		game->keys.shift = 0;
	if (game->keys.a || game->keys.s || game->keys.d || game->keys.w)
		game->player.moving = 1;
	else
		game->player.moving = 0;
	menu_keys_release(key, game);
	return (0);
}

/*condition space not pressed has to be here and not in key_release to only
have one jump per space press*/
void	keys_action(t_game *game)
{
	keys_movement(game);
	keys_rotation(game);
	keys_menu(game);
}
