/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:25:59 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/08 17:09:06 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_philo
{
	int	id;
	long int		last_eat_time;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *nptr);

#endif
