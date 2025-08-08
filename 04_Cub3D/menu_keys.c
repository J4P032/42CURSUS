/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:05:46 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/08 10:21:42 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keys_menu(t_game *game)
{
	if (game->keys.m && !game->keys.m_was_pressed)
	{
		game->player.mouse_control = !game->player.mouse_control;
		game->keys.m_was_pressed = 1;
	}
	else if (!game->keys.m)
		game->keys.m_was_pressed = 0;
}

