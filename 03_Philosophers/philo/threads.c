/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:54:49 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/09 21:37:20 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_function(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	//inicializar la nueva t_game *game en cada filosofo para tener todos los datos.
	//philo->game debe apuntar a la estructura game.
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
	gettimeofday(&game->start_game_time, NULL);//mejor esperar al GOOOO
	while (i < game->num_philos)
	{
		pthread_mutex_init(&aux->fork, NULL); //no hace malloc pero hay que liberar recursos con un pthread_mutex_destroy(&mutex)
		aux->last_eat_time = game->start_game_time;
		aux->game = game;
		error = pthread_create(&aux->thread, NULL, thread_function, aux);
		if (error)
			return (0);
		aux = aux->next;
		i++;
	}
	return (1);
}
