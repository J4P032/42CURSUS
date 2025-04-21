/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:00:05 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/21 22:01:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*This is for modifing the variable of each philo to see if he toke the fork..*/
/*...or not. So it is protected by a general mutex instead the each philo ones*/
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

/*This is for the ODD id philos. They will wait some time to not make a...*/
/*...deadlock with the EVEN ones. If the philo see that the fork that is...*/
/*...going to pickup is already taken, It will leave and wait next time...*/
/*ODDs will take first the right one (self one), so if it already taken...*/
/*...they will just exit. Then will see if left fork is taken. If so they...*/
/*...will just leave the right fork taken and exit waiting for next time*/
/*Because I dont want to print fork taken several times in case he has to...*/
/*leave them, I just print both same time when taken the second fork. Time...*/
/*...that pass between the first fork taken and the second to see is minimun*/
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

/*Same as ODDs but opposite. This ones dont wait anything to pick forks*/
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

/*asign the return from both functions to value as it is faster...*/
/*...instead of if(!take_first_right_fork(philo))*/
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
