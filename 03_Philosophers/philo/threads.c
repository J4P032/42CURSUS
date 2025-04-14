/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:54:49 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/14 08:29:03 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_without_eatting(t_philo *philo)
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

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
		usleep(100);
	if (philo->next->id == 1)
	{
		pthread_mutex_lock(&philo->fork);
		write_log(philo, 'f');
		pthread_mutex_lock(&philo->prev->fork);
		write_log(philo, 'f');
	}
	else
	{	
		pthread_mutex_lock(&philo->prev->fork);
		write_log(philo, 'f');
		pthread_mutex_lock(&philo->fork);
		write_log(philo, 'f');
	}
	gettimeofday(&philo->last_eat_time, NULL);
	write_log(philo, 'e');
	usleep(philo->game->time_2_eat * 1000);
	pthread_mutex_unlock(&philo->prev->fork);
	pthread_mutex_unlock(&philo->fork);
	philo->times_eatten++;
}

void	*judge_time(void *arg)
{
	t_game		*game;
	t_philo		*aux;
	
	game = (t_game *)arg;
	aux = game->philo;
	while (!game->running)
		usleep(1000);
	while (game->running)
	{
		if (time_without_eatting(aux) > game->time_2_die)
		{
			write_log(aux, 'd');
			break ;
		}
		if (aux->times_eatten == game->num_times_2_eat && !aux->eatten_min)
		{
			game->philos_eatten++;//cuidado quiza cuenta varias veces mismo philo?
			aux->eatten_min = 1;
		}
		if (game->philos_eatten == game->num_philos)
			game->running = 0;
		aux = aux->next;	
	}
	printf("PASA POR AQUI!!!!!!!");
	//free mutex
	return (NULL);
}

void	*thread_function(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (!philo->game->running)
		usleep(1000);
	//gettimeofday(&philo->game->start_game_time, NULL);//
	//philo->last_eat_time = philo->game->start_game_time;//
	while (philo->game->running)
	{
		philo_eat(philo);
		write_log(philo, 's');
		usleep(philo->game->time_2_sleep * 1000);
		write_log(philo, 't');
		//usleep( (philo->game->time_2_eat - philo->game->time_2_sleep) * 1000 / 2 ); //de chatgpt para evitar que se sincronicen y mueran todos de golpe.
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
	init_time(game);//
	while (i < game->num_philos)
	{
		pthread_mutex_init(&aux->fork, NULL); //no hace malloc pero hay que liberar recursos con un pthread_mutex_destroy(&mutex)
		aux->game = game;
		error = pthread_create(&aux->thread, NULL, thread_function, aux);
		if (error)
			return (0);
		aux = aux->next;
		i++;
	}
	error = pthread_create(&game->judge, NULL, judge_time, game);//hay que crear un hilo juez que sea el que mide los tiempos de comer ya que se puede bloquear el propio filosofo mientras espera el tenedor y morir mientras espera por lo que pasa un tiempo desde que muere hasta la linea donde compruebo. Este hilo no espera.
	if (error)
		return (0);
	game->running = 1;
	return (1);
}
