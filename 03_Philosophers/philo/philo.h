/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:25:59 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/09 17:53:39 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>

# define PHILOS_MAX 250

typedef struct		s_philo
{
	int				id;
	pthread_t       thread;
	struct timeval	last_eat_time;
	pthread_mutex_t	*fork;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

typedef struct		s_game
{
	long			num_philos;
	long			time_2_die;
	long			time_2_eat;
	long			time_2_sleep;
	long			num_times_2_eat;
	int				running;
	pthread_mutex_t	writing;
	struct timeval	start_game_time;
	t_philo			*philo;
}					t_game;

void		*ft_calloc(size_t nmemb, size_t size);
long int	ft_atol(char *nptr, int *error);
void		free_all(t_game *game);

#endif
