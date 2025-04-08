/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:25:59 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/08 21:25:23 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct		s_philo
{
	int				id;
	pthread_t       thread;
	long int		last_eat_time;
	pthread_mutex_t	*fork;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

typedef struct		s_game
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_times_to_eat;
	pthread_mutex_t	writing;
	t_philo			*philo;
}					t_game;

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *nptr);

#endif
