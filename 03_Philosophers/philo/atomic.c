/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:01:54 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/14 17:47:39 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_game_running(t_game *game, int value)
{
	pthread_mutex_lock(&game->running_mutex);
	game->running = value;
	pthread_mutex_unlock(&game->running_mutex);
}

void	read_game_running(t_game *game, int *running)
{
	pthread_mutex_lock(&game->running_mutex);
	*running = game->running;
	pthread_mutex_unlock(&game->running_mutex);
}
