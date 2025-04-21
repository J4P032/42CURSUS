/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:15:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/21 21:52:03 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*It can die while it is eating if time to survive is less than time need to..*/
/*...eat. Also can die while he is sleeping. I look every TIME_WAIT time*/
void	philo_eat_sleep_think_times(t_philo *philo, char c)
{
	if (c == 'e' && !i_died(philo))
	{
		gettimeofday(&philo->last_eat_time, NULL);
		write_log(philo, 'e');
		while (!i_died(philo) && time_no_eat(philo) < philo->game->time_2_eat)
			usleep(TIME_WAIT);
	}
	else if (!i_died(philo))
	{
		gettimeofday(&philo->sleep_time, NULL);
		write_log(philo, 's');
		while (!i_died(philo) && time_sleep(philo) < philo->game->time_2_sleep)
			usleep(TIME_WAIT);
		write_log(philo, 't');
	}
}

/*pick forks is complex. If he has grabed a fork but the other is not...*/
/*...free it will leave the grabed one, and retry later.*/
int	philo_eat(t_philo *philo)
{
	if (!philos_pick_forks(philo))
		return (0);
	pthread_mutex_lock(&philo->eat_mutex);
	philo_eat_sleep_think_times(philo, 'e');
	philo->times_eatten++;
	check_min_eat_times(philo);
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_unlock(&philo->fork);
	take_one_fork(philo, 'r');
	pthread_mutex_unlock(&philo->prev->fork);
	take_one_fork(philo, 'l');
	return (1);
}
