/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:04:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/13 17:06:56 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_time(t_game *game)
{
	t_philo	*aux;
	//inicializar el tiempo.	
	aux = game->philo;
	gettimeofday(&game->start_game_time, NULL);//
	aux->last_eat_time = game->start_game_time;
	aux = aux->next;
	while (aux->id != 1)
	{
		aux->last_eat_time = game->start_game_time;
		aux = aux->next;
	}
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
	pthread_mutex_lock(&philo->game->writing);
	printf("%lu\t", log_time(philo->game));
	if (c == 'f' && philo->game->running)
		printf("%d has taken a fork\n", philo->id);
	else if (c == 'e' && philo->game->running)
		printf("%d is eating\n", philo->id);
	else if (c == 's' && philo->game->running)
		printf("%d is sleeping\n", philo->id);
	else if (c == 't' && philo->game->running)
		printf("%d is thinking\n", philo->id);
	else if (c == 'd' && philo->game->running)
	{
		printf("%d has DIED!!\n", philo->id);
		philo->game->running = 0;
		//usleep(1000000);
	}
	pthread_mutex_unlock(&philo->game->writing);
}
