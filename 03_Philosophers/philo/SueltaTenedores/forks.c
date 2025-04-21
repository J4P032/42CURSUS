/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:00:05 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/21 18:03:15 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	take_first_right_fork(t_philo *philo)
{
	usleep(philo->game->odd_philos_to_wait);
	pthread_mutex_lock(&philo->game->forks);
	if (philo->fork_taken)
	{
		pthread_mutex_unlock(&philo->game->forks);
		return (0);
	}
	pthread_mutex_unlock(&philo->game->forks);
	pthread_mutex_lock(&philo->fork);
	take_one_fork(philo, 'R');
	pthread_mutex_lock(&philo->game->forks);
	if (philo->prev->fork_taken)
	{
		pthread_mutex_unlock(&philo->game->forks);
		pthread_mutex_unlock(&philo->fork);
		take_one_fork(philo, 'r');
		return (0);
	}
	pthread_mutex_unlock(&philo->game->forks);
	pthread_mutex_lock(&philo->prev->fork);
	write_log(philo, 'r');
	write_log(philo, 'l');
	take_one_fork(philo, 'L');
	return (1);
}

int	take_first_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->forks);
	if (philo->prev->fork_taken)
	{
		pthread_mutex_unlock(&philo->game->forks);
		return (0);
	}
	pthread_mutex_unlock(&philo->game->forks);
	pthread_mutex_lock(&philo->prev->fork);
	take_one_fork(philo, 'L');
	pthread_mutex_lock(&philo->game->forks);
	if (philo->fork_taken)
	{
		pthread_mutex_unlock(&philo->game->forks);
		pthread_mutex_unlock(&philo->prev->fork);
		take_one_fork(philo, 'l');
		return (0);
	}
	pthread_mutex_unlock(&philo->game->forks);
	pthread_mutex_lock(&philo->fork);
	write_log(philo, 'l');
	write_log(philo, 'r');
	take_one_fork(philo, 'R');
	return (1);
}

int	philos_pick_forks(t_philo *philo)
{
	int	value;

	if (i_died(philo))
		return (0);
	if (philo->id % 2 != 0)
	{
		value = take_first_right_fork(philo);
		if (!value)
			return (0);
	}
	else
	{
		value = take_first_left_fork(philo);
		if (!value)
			return (0);
	}
	return (1);
}
