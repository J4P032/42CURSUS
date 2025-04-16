/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:54:49 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/15 17:50:06 by jrollon-         ###   ########.fr       */
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
		usleep(1003); //1000 funciona muy bien pero no perfecto
	pthread_mutex_lock(&philo->prev->fork);
	write_log(philo, 'f');
	pthread_mutex_lock(&philo->fork);
	write_log(philo, 'f');
	pthread_mutex_lock(&philo->eat_mutex);
	gettimeofday(&philo->last_eat_time, NULL);
	write_log(philo, 'e');
	usleep(philo->game->time_2_eat * 1000);
	philo->times_eatten++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->prev->fork);
	pthread_mutex_unlock(&philo->eat_mutex);//*
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
		pthread_mutex_lock(&aux->eat_mutex);//*
		if (time_without_eatting(aux) > game->time_2_die)
		{
			pthread_mutex_unlock(&aux->eat_mutex);//*
			write_log(aux, 'd');
			break ;
		}
		pthread_mutex_unlock(&aux->eat_mutex);//*
		if (check_min_eat_times(game, aux))
			break ;
		aux = aux->next;	
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
		philo_eat(philo);
		write_log(philo, 's');
		usleep(philo->game->time_2_sleep * 1000);
		write_log(philo, 't');
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
	init_time(game);//
	while (i < game->num_philos)
	{
		pthread_mutex_init(&aux->fork, NULL); //no hace malloc pero hay que liberar recursos con un pthread_mutex_destroy(&mutex)
		pthread_mutex_init(&aux->eat_mutex, NULL);//*
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
	game_running(game, 1);
	return (1);
}




/*POSIBLE DEADBLOCK POR TOMAR TENEDORES CHUNGO POSIBLE SOLUCION DE CLAUDE

// Para adquirir los tenedores (donde sea que esté este código)
if (philo->id % 2 == 0) {  // Filósofos pares
    pthread_mutex_lock(&philo->fork);  // Primero el tenedor derecho
    write_log(philo, 'f');
    pthread_mutex_lock(&philo->prev->fork);  // Luego el izquierdo
    write_log(philo, 'f');
} else {  // Filósofos impares
    pthread_mutex_lock(&philo->prev->fork);  // Primero el tenedor izquierdo
    write_log(philo, 'f');
    pthread_mutex_lock(&philo->fork);  // Luego el derecho
    write_log(philo, 'f');
}

O

// Siempre tomar los tenedores en orden de ID menor a mayor
if (philo->id < philo->prev->id) {
    pthread_mutex_lock(&philo->fork);
    write_log(philo, 'f');
    pthread_mutex_lock(&philo->prev->fork);
    write_log(philo, 'f');
} else {
    pthread_mutex_lock(&philo->prev->fork);
    write_log(philo, 'f');
    pthread_mutex_lock(&philo->fork);
    write_log(philo, 'f');
}


*/
