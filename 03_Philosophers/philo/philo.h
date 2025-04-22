/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:25:59 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/22 09:27:33 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>

# define PHILOS_MAX 250
# define TIME_WAIT 1

typedef struct s_game	t_game;

typedef struct s_philo
{
	int				id;
	int				died;
	long			times_eatten;
	int				eatten_min;
	struct timeval	last_eat_time;
	struct timeval	sleep_time;
	int				fork_taken;
	pthread_t		thread;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	fork;
	struct s_philo	*next;
	struct s_philo	*prev;
	t_game			*game;
}					t_philo;

typedef struct s_game
{
	long			num_philos;
	long			time_2_die;
	long			time_2_eat;
	long			time_2_sleep;
	long			num_times_2_eat;
	long			philos_eatten;
	int				odd_philos_to_wait;
	int				running;
	int				one_died;
	pthread_t		judge;
	pthread_mutex_t	forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	running_mutex;
	pthread_mutex_t	writing;
	struct timeval	start_game_time;
	t_philo			*philo;
}					t_game;

void		*ft_calloc(size_t nmemb, size_t size);
int			arg_errors(int argc, t_game *game, int error, int option);
long int	ft_atol(char *nptr, int *error);
void		free_all(t_game *game);
int			create_threads(t_game *game);
void		write_log(t_philo *philo, int c);
void		init_time(t_game *game);
void		mutex_destroyer(t_game *game);
void		check_min_eat_times(t_philo *aux);
int			game_running(t_game *game, int value);
long		time_sleep(t_philo *philo);//
long		time_no_eat(t_philo *philo);
int			i_died(t_philo *philo);
int			philo_eat(t_philo *philo);
void		philo_eat_sleep_think_times(t_philo *philo, char c);
int			philos_pick_forks(t_philo *philo);
void		take_one_fork(t_philo *philo, int c);
void		write_death(t_philo *philo);
long		log_time(t_game *game);
void		check_all_eated(t_philo *philo);

#endif
