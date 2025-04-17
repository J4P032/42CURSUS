/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:54:49 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/17 17:46:00 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat_sleep_think_times(t_philo *philo, char c)
{
	if (c == 'e' && !i_died(philo))
	{
		gettimeofday(&philo->last_eat_time, NULL);
		write_log(philo, 'e');
		while (!i_died(philo) && time_no_eating(philo) < philo->game->time_2_eat)
			usleep(1000);
		return ;
	}
	else if (!i_died(philo))
	{
		gettimeofday(&philo->sleep_time, NULL);
		write_log(philo, 's');
		while (!i_died(philo) && time_sleeping(philo) < philo->game->time_2_sleep)
			usleep(1000);
		write_log(philo, 't');
	}
}

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork);
		write_log(philo, 'r');
		pthread_mutex_lock(&philo->prev->fork);
		write_log(philo, 'l');
	}
	else
	{
		pthread_mutex_lock(&philo->prev->fork);
		write_log(philo, 'l');
		pthread_mutex_lock(&philo->fork);
		write_log(philo, 'r');
	}
	pthread_mutex_lock(&philo->eat_mutex);
	philo_eat_sleep_think_times(philo, 'e');//
	philo->times_eaten++;
	check_min_eat_times(philo);//
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->prev->fork);
	pthread_mutex_unlock(&philo->eat_mutex);//
}

void	*judge_time(void *arg)
{
	t_game		*game;
	t_philo		*aux;
	
	game = (t_game *)arg;
	aux = game->philo;
	while (!game_running(game, -1))
		usleep(1000);//estos numeros importantisimo. funciona bien 1000
	while (game_running(game, -1))
	{
		pthread_mutex_lock(&game->death_mutex);
		if (game->one_died)
		{
			write_log(aux, 'd');
			pthread_mutex_unlock(&game->death_mutex);
			break ;
		}	
		if (game->philos_eaten > game->num_philos - 1)
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
	t_philo *philo;

	philo = (t_philo *)arg;
	while (!game_running(philo->game, -1))
		usleep(1000); //estos numeros importantisimo. funciona bien 1000
	while (game_running(philo->game, -1))
	{
		if (philo->game->num_philos != 1)
		{
			if (!i_died(philo))
				philo_eat(philo);
			philo_eat_sleep_think_times(philo, 's');
		}
		else
		{
			pthread_mutex_lock(&philo->fork);
			write_log(philo, 'r');
			usleep(philo->game->time_2_die * 1000);
			pthread_mutex_unlock(&philo->fork);
			i_died(philo);
			break ;
		}
	}
	//mutex_destroyer(philo->game);
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
	pthread_mutex_init(&game->death_mutex, NULL);///
	while (i++ < game->num_philos)
	{
		pthread_mutex_init(&aux->fork, NULL); //no hace malloc pero hay que liberar recursos con un pthread_mutex_destroy(&mutex)
		pthread_mutex_init(&aux->eat_mutex, NULL);//
		aux->game = game;
		error = pthread_create(&aux->thread, NULL, thread_function, aux);
		if (error)
			return (0);
		aux = aux->next;
	}
	error = pthread_create(&game->judge, NULL, judge_time, game);//hay que crear un hilo juez que sea el que mide los tiempos de comer ya que se puede bloquear el propio filosofo mientras espera el tenedor y morir mientras espera por lo que pasa un tiempo desde que muere hasta la linea donde compruebo. Este hilo no espera.
	if (error)
		return (0);
	init_time(game); // lo he movido desde arriba del while para que empieze en cero.
	return (1);
}

