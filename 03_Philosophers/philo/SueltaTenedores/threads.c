/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:54:49 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/21 22:13:31 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Do 2 things. Check the variable to see if someone died all the time, so...*/
/*...the quickest possible. And also check that all philos has eatten the...*/
/*...minimun times. Last usleep of 1000 is for not writting junk at the end*/
void	*judge_time(void *arg)
{
	t_game		*game;
	t_philo		*aux;

	game = (t_game *)arg;
	aux = game->philo;
	while (!game_running(game, -1))
		usleep(1);
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
	return (usleep(1000), NULL);
}

void	only_one_philo_try_to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	write_log(philo, 'r');
	while (!i_died(philo))
		usleep(5);
	pthread_mutex_unlock(&philo->fork);
}

/*The magic number is 1000 or 2000 in usleep. It will give more time of...*/
/*...thinking when succseeded. Philos that dont take the forks because ocupied*/
/*...will pass quick to try again. One philo is not with trick. Just pick fork*/
/*...and see if he dies. He will, but not forced.*/
void	*thread_function(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!game_running(philo->game, -1))
		usleep(1);
	while (game_running(philo->game, -1))
	{
		if (philo->game->num_philos != 1)
		{
			if (philo_eat(philo))
			{
				philo_eat_sleep_think_times(philo, 's');
				usleep(1000);
			}
		}
		else
		{
			only_one_philo_try_to_eat(philo);
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
	while (i++ < game->num_philos)
	{
		pthread_mutex_init(&aux->fork, NULL);
		pthread_mutex_init(&aux->eat_mutex, NULL);
		aux->game = game;
		error = pthread_create(&aux->thread, NULL, thread_function, aux);
		if (error)
			return (0);
		aux = aux->next;
	}
	error = pthread_create(&game->judge, NULL, judge_time, game);
	if (error)
		return (0);
	init_time(game);
	return (1);
}
