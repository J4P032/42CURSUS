/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:04:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/19 21:49:34 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroyer(t_game *game)
{
	t_philo	*aux;

	aux = game->philo;
	pthread_mutex_destroy(&aux->fork);
	pthread_mutex_destroy(&aux->eat_mutex);
	aux = aux->next;
	while (aux->id != 1)
	{
		pthread_mutex_destroy(&aux->fork);
		pthread_mutex_destroy(&aux->eat_mutex);
		aux = aux->next;
	}
	pthread_mutex_destroy(&game->forks);
	pthread_mutex_destroy(&game->death_mutex);
	pthread_mutex_destroy(&game->running_mutex);
	pthread_mutex_destroy(&game->writing);
}

void	check_min_eat_times(t_philo *aux)
{
	pthread_mutex_lock(&aux->game->death_mutex);
	if (aux->times_eatten == aux->game->num_times_2_eat && !aux->eatten_min)
	{
		aux->game->philos_eatten++;
		aux->eatten_min = 1;
	}
	pthread_mutex_unlock(&aux->game->death_mutex);
}

void	init_time(t_game *game)
{
	if (game->num_philos < 50)
		game->odd_philos_to_wait = 1003;
	else
		game->odd_philos_to_wait = 10003;
}

long	log_time(t_game *game)
{
	struct timeval	time;
	time_t			dif_seconds;
	suseconds_t		dif_useconds;
	long int		dif_time;

	gettimeofday(&time, NULL);
	dif_seconds = time.tv_sec - game->start_game_time.tv_sec;
	dif_useconds = time.tv_usec - game->start_game_time.tv_usec;
	dif_time = (dif_seconds * 1000) + (dif_useconds / 1000);
	return (dif_time);
}

void	write_log(t_philo *philo, int c)
{
	t_philo	*aux;

	aux = philo;
	pthread_mutex_lock(&philo->game->writing);
	if (game_running(philo->game, -1))
		printf("🕖%lu\t", log_time(philo->game));
	if (c == 'r' && game_running(philo->game, -1))
		printf("🥄%d has taken the R-Fork\n", philo->id);
	else if (c == 'l' && game_running(philo->game, -1))
		printf("🥄%d has taken the L-Fork\n", philo->id);
	else if (c == 'e' && game_running(philo->game, -1))
		printf("🍔%d is eating\n", philo->id);
	else if (c == 's' && game_running(philo->game, -1))
		printf("😴%d is sleeping\n", philo->id);
	else if (c == 't' && game_running(philo->game, -1))
		printf("🙄%d is thinking\n", philo->id);
	else if (c == 'd' && game_running(philo->game, -1))
	{
		while (!aux->died)
			aux = aux->next;
		game_running(philo->game, 0);
		printf("☠️%d has DIED!!\n", aux->id);
	}
	pthread_mutex_unlock(&philo->game->writing);
}
