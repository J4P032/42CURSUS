/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:04:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/16 09:26:03 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroyer(t_game *game)
{
	t_philo	*aux;
	
	aux = game->philo;
	
	/* pthread_mutex_unlock(&game->writing);
	pthread_mutex_unlock(&aux->fork);
	pthread_mutex_unlock(&aux->eat_mutex);
	aux = aux->next;
	while (aux->id != 1)
	{
		pthread_mutex_unlock(&aux->fork);
		pthread_mutex_unlock(&aux->eat_mutex);
		aux = aux->next;
	} */
	pthread_mutex_destroy(&aux->fork);
	pthread_mutex_destroy(&aux->eat_mutex);
	aux = aux->next;
	while (aux->id != 1)
	{
		pthread_mutex_destroy(&aux->fork);
		pthread_mutex_destroy(&aux->eat_mutex);
		aux = aux->next;
	}
	pthread_mutex_destroy(&game->writing);
}

int	check_min_eat_times(t_game *game, t_philo *aux)
{
	if (aux->times_eatten == game->num_times_2_eat && !aux->eatten_min)
	{
		game->philos_eatten++;
		aux->eatten_min = 1;
	}
	if (game->philos_eatten > game->num_philos - 1)
	{
		game_running(game, 0);
		return (1);
	}
	return (0);
}

void	init_time(t_game *game)
{
	t_philo	*aux;
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
	if (game_running(philo->game, -1))
		printf("%lu\t", log_time(philo->game));
	if (c == 'f' && game_running(philo->game, -1))
		printf("%d has taken a fork\n", philo->id);
	else if (c == 'e' && game_running(philo->game, -1))
		printf("%d is eating\n", philo->id);
	else if (c == 's' && game_running(philo->game, -1))
		printf("%d is sleeping\n", philo->id);
	else if (c == 't' && game_running(philo->game, -1))
		printf("%d is thinking\n", philo->id);
	else if (c == 'd' && game_running(philo->game, -1))
	{
		game_running(philo->game, 0);
		printf("%d has DIED!!\n", philo->id);
		pthread_mutex_unlock(&philo->fork); //este es unlock de uno que no esta lock pero lo necesito para salir
		//pthread_mutex_destroy(&philo->game->writing); //este provoca un destroy de un lock que sigue estando lock
	}
	pthread_mutex_unlock(&philo->game->writing);
}
