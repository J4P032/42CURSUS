/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:01:54 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/16 20:35:15 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_sleeping(t_philo *philo)
{
	struct timeval	time;
	time_t			dif_seconds;
	suseconds_t		dif_useconds;
	long int		dif_time;

	gettimeofday(&time, NULL);
	dif_seconds = time.tv_sec - philo->sleep_time.tv_sec;
	dif_useconds = time.tv_usec - philo->sleep_time.tv_usec;
	dif_time = (dif_seconds * 1000) + (dif_useconds / 1000);
	return (dif_time);
}


long	time_no_eating(t_philo *philo)
{
	struct timeval	time;
	time_t			dif_seconds;
	suseconds_t		dif_useconds;
	long int		dif_time;

	gettimeofday(&time, NULL);
	dif_seconds = time.tv_sec - philo->last_eat_time.tv_sec;
	dif_useconds = time.tv_usec - philo->last_eat_time.tv_usec;
	dif_time = (dif_seconds * 1000) + (dif_useconds / 1000);
	return (dif_time);
}

int	i_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->death_mutex);
	if (time_no_eating(philo) > philo->game->time_2_die)
	{
		philo->game->one_died = 1;
		philo->died = 1;
		pthread_mutex_unlock(&philo->game->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->game->death_mutex);
	return (0);
}

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
		
