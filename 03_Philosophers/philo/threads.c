/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:54:49 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/17 15:18:47 by jrollon-         ###   ########.fr       */
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
		usleep(50);
	return ;
	}
	else if (!i_died(philo))
	{
		gettimeofday(&philo->sleep_time, NULL);//
		write_log(philo, 's');
		while (!i_died(philo) && time_sleeping(philo) < philo->game->time_2_sleep)
			usleep(50);
		write_log(philo, 't');
	}
}

int	access_both_forks(t_philo *philo)
{
	int  mine = philo->id;
	int  prev = philo->prev->id;
	t_philo *first = (mine < prev) ? philo : philo->prev;
	t_philo *second = (mine < prev) ? philo->prev : philo;
	
	pthread_mutex_lock(&first->eat_mutex);
	pthread_mutex_lock(&second->eat_mutex);
	
	while (!i_died(philo) && (philo->fork_taken || philo->prev->fork_taken))
		usleep(100);
	
	if (i_died(philo))
	{
		pthread_mutex_unlock(&second->eat_mutex);
		pthread_mutex_unlock(&first->eat_mutex);
		return 0;
	}
	
	// ya no necesitamos eat_mutex para chequear flags
	pthread_mutex_unlock(&second->eat_mutex);
	pthread_mutex_unlock(&first->eat_mutex);
	return 1;
}

//
/* int	access_both_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	pthread_mutex_lock(&philo->prev->eat_mutex);
	while (!i_died(philo) && (philo->fork_taken || philo->prev->fork_taken))
		usleep(100);
	if (i_died(philo))
	{
		pthread_mutex_unlock(&philo->prev->eat_mutex);
		pthread_mutex_unlock(&philo->eat_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->prev->eat_mutex);
	pthread_mutex_unlock(&philo->eat_mutex);
	return (1);
} */

void	access_fork(t_philo *philo, int c)
{
	if (c == 'R')
	{
		pthread_mutex_lock(&philo->eat_mutex);
		philo->fork_taken = 1;
		pthread_mutex_unlock(&philo->eat_mutex);
	}
	else if (c == 'L')
	{
		pthread_mutex_lock(&philo->prev->eat_mutex);
		philo->prev->fork_taken = 1;
		pthread_mutex_unlock(&philo->prev->eat_mutex);
	}
	if (c == 'r')
	{
		pthread_mutex_lock(&philo->eat_mutex);
		philo->fork_taken = 0;
		pthread_mutex_unlock(&philo->eat_mutex);
	}
	else if (c == 'l')
	{
		pthread_mutex_lock(&philo->prev->eat_mutex);
		philo->prev->fork_taken = 0;
		pthread_mutex_unlock(&philo->prev->eat_mutex);
	}
}


void	philo_eat(t_philo *philo)
{
	
	if (!access_both_forks(philo))
		return ;
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork);
		write_log(philo, 'r');
		access_fork(philo, 'R');
		pthread_mutex_lock(&philo->prev->fork);
		write_log(philo, 'l');
		access_fork(philo, 'L');
	}
	else
	{
		pthread_mutex_lock(&philo->prev->fork);
		write_log(philo, 'l');
		access_fork(philo, 'L');
		pthread_mutex_lock(&philo->fork);
		write_log(philo, 'r');
		access_fork(philo, 'R');
	}
	if (i_died(philo))
		return ;
	pthread_mutex_lock(&philo->eat_mutex);
	philo_eat_sleep_think_times(philo, 'e');//
	philo->times_eatten++;
	pthread_mutex_unlock(&philo->eat_mutex);//*
	check_min_eat_times(philo);//
	
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->prev->fork);
		access_fork(philo, 'l');
		pthread_mutex_unlock(&philo->fork);
		access_fork(philo, 'r');
	}
	else
	{
		pthread_mutex_unlock(&philo->fork);
		access_fork(philo, 'r');
		pthread_mutex_unlock(&philo->prev->fork);
		access_fork(philo, 'l');
	}
}



/* void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork);
		write_log(philo, 'r');
		if (i_died(philo))
		{
			pthread_mutex_unlock(&philo->fork);
			return ;
		}
		pthread_mutex_lock(&philo->prev->fork);
		write_log(philo, 'l');
	}
	else
	{
		pthread_mutex_lock(&philo->prev->fork);
		write_log(philo, 'l');
		if (i_died(philo))
		{
			pthread_mutex_unlock(&philo->prev->fork);
			return ;
		}
		pthread_mutex_lock(&philo->fork);
		write_log(philo, 'r');
	}
	pthread_mutex_lock(&philo->eat_mutex);
	philo_eat_sleep_think_times(philo, 'e');//
	philo->times_eatten++;
	check_min_eat_times(philo);//
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->prev->fork);
	pthread_mutex_unlock(&philo->eat_mutex);//
} */

void	*judge_time(void *arg)
{
	t_game		*game;
	t_philo		*aux;
	
	game = (t_game *)arg;
	aux = game->philo;
	while (!game_running(game, -1))
		usleep(1);//estos numeros importantisimo. funciona bien 1000
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
	t_philo *philo;

	philo = (t_philo *)arg;
	while (!game_running(philo->game, -1))
		usleep(1); //estos numeros importantisimo. funciona bien 1000
	while (game_running(philo->game, -1))
	{
		if (philo->game->num_philos != 1)
		{
			if (!i_died(philo))///
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

