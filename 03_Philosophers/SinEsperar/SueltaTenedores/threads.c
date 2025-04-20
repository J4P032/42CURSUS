/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:54:49 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/20 02:12:59 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*judge_time(void *arg)
{
	t_game		*game;
	t_philo		*aux;

	game = (t_game *)arg;
	aux = game->philo;
	while (game_running(game, -1))
	{
		pthread_mutex_lock(&game->death_mutex);
		if (game->one_died)
		{
			write_log(aux, 'd');
			pthread_mutex_unlock(&game->death_mutex);
			break ;
		}
		if (game->philos_eatten > game->num_philos - 1)
		{
			game_running(game, 0);
			pthread_mutex_unlock(&game->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&game->death_mutex);
	}
	return (NULL);
}

void	*thread_function(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (game_running(philo->game, -1))
	{
		if (philo->game->num_philos != 1)
		{
			if (philo_eat(philo))
			{
				philo_eat_sleep_think_times(philo, 's');
				usleep(50);
			}
		}
		else
		{
			pthread_mutex_lock(&philo->fork);
			write_log(philo, 'r');
			while (!i_died(philo))
				usleep(5);
			pthread_mutex_unlock(&philo->fork);
			break ;
		}
	}
	return (NULL);
}

/*pthread_create returns 0 if it is ok. Anything else if wrong...*/
/*...I return 0 if error in this create_threads func to allow out free all*/
int	create_threads(t_game *game)
{
	long	i;
	int		error;
	t_philo	*aux;

	i = 0;
	error = 0;
	aux = game->philo;
	pthread_mutex_init(&game->writing, NULL);
	pthread_mutex_init(&game->running_mutex, NULL);
	pthread_mutex_init(&game->death_mutex, NULL);
	pthread_mutex_init(&game->forks, NULL);
	while (i++ < game->num_philos)
	{
		pthread_mutex_init(&aux->fork, NULL);
		pthread_mutex_init(&aux->eat_mutex, NULL);
		aux->game = game;
		aux = aux->next;
	}
	i = 0;
	aux = game->philo;
	game_running(game, 1);
	gettimeofday(&game->start_game_time, NULL);
	init_time(game);
	while (i++ < game->num_philos)
	{
		gettimeofday(&aux->last_eat_time, NULL);
		error = pthread_create(&aux->thread, NULL, thread_function, aux);
		if (error)
			return (0);
		aux = aux->next;
	}
	error = pthread_create(&game->judge, NULL, judge_time, game);
	if (error)
		return (0);
	return (1);
}
