/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:01:54 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/15 16:00:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	game_running(t_game *game, int value)
{
	int	run;
	
	pthread_mutex_lock(&game->running_mutex);
	if (value > -1)
		game->running = value;
	run = game->running;
	pthread_mutex_unlock(&game->running_mutex);
	return (run);
}
		
