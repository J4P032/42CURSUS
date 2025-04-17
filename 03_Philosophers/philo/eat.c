/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:15:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/17 20:46:20 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat_sleep_think_times(t_philo *philo, char c)
{
	if (c == 'e' && !i_died(philo))
	{
		gettimeofday(&philo->last_eat_time, NULL);
		write_log(philo, 'e');
		while (!i_died(philo) && time_no_eat(philo) < philo->game->time_2_eat)
			usleep(1);
	}
	else if (!i_died(philo))
	{
		gettimeofday(&philo->sleep_time, NULL);
		write_log(philo, 's');
		while (!i_died(philo) && time_sleep(philo) < philo->game->time_2_sleep)
			usleep(1);
		write_log(philo, 't');
	}
}

int	take_both_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->forks);
	while (!i_died(philo) && (philo->fork_taken || philo->prev->fork_taken))
	{
		pthread_mutex_unlock(&philo->game->forks);
		usleep(1);
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

void	philos_behaviour(t_philo *philo)
{
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
}

void	philo_eat(t_philo *philo)
{
	if (!take_both_forks(philo))
		return ;
	philos_behaviour(philo);
	pthread_mutex_lock(&philo->eat_mutex);
	philo_eat_sleep_think_times(philo, 'e');
	philo->times_eatten++;
	check_min_eat_times(philo);
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_unlock(&philo->fork);
	take_one_fork(philo, 'r');
	pthread_mutex_unlock(&philo->prev->fork);
	take_one_fork(philo, 'l');
}
