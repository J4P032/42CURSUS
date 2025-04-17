/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:54:49 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/17 18:47:50 by jrollon-         ###   ########.fr       */
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










int	take_both_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->forks);
	while (!i_died(philo) && (philo->fork_taken || philo->prev->fork_taken))
	{
		pthread_mutex_unlock(&philo->game->forks);
		usleep(50);
		pthread_mutex_lock(&philo->game->forks);
	}
	pthread_mutex_unlock(&philo->game->forks);
	if (i_died(philo))
		return (0);
	return (1);
}


void	take_one_fork(t_philo *philo, int c)
{
	if (c == 'R')
	{
		pthread_mutex_lock(&philo->game->forks);
		philo->fork_taken = 1;
		pthread_mutex_unlock(&philo->game->forks);
	}
	if (c == 'L')
	{
		pthread_mutex_lock(&philo->game->forks);
		philo->prev->fork_taken = 1;
		pthread_mutex_unlock(&philo->game->forks);
	}
	if (c == 'r')
	{
		pthread_mutex_lock(&philo->game->forks);
		philo->fork_taken = 0;
		pthread_mutex_unlock(&philo->game->forks);
	}
	if (c == 'l')
	{
		pthread_mutex_lock(&philo->game->forks);
		philo->prev->fork_taken = 0;
		pthread_mutex_unlock(&philo->game->forks);
	}
}



void	philo_eat(t_philo *philo)
{
	if (!take_both_forks(philo))
		return ;
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork);
		write_log(philo, 'r');
		take_one_fork(philo, 'R');
		pthread_mutex_lock(&philo->prev->fork);
		write_log(philo, 'l');
		take_one_fork(philo, 'L');
	}
	else
	{
		pthread_mutex_lock(&philo->prev->fork);
		write_log(philo, 'l');
		take_one_fork(philo, 'L');
		pthread_mutex_lock(&philo->fork);
		write_log(philo, 'r');
		take_one_fork(philo, 'R');
	}
	pthread_mutex_lock(&philo->eat_mutex);
	philo_eat_sleep_think_times(philo, 'e');
	philo->times_eatten++;
	check_min_eat_times(philo);//
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_unlock(&philo->fork);
	take_one_fork(philo, 'r');
	pthread_mutex_unlock(&philo->prev->fork);
	take_one_fork(philo, 'l');
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
			//if (!i_died(philo))
			philo_eat(philo);
			philo_eat_sleep_think_times(philo, 's');
		}
		else
		{
			pthread_mutex_lock(&philo->fork);
			write_log(philo, 'f');
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
	pthread_mutex_init(&game->death_mutex, NULL);
	pthread_mutex_init(&game->forks, NULL);////
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
	error = pthread_create(&game->judge, NULL, judge_time, game);//hilo juez
	if (error)
		return (0);
	init_time(game); // lo he movido desde arriba del while para que empieze en cero.
	return (1);
}

