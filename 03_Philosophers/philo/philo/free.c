/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:56:01 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/09 17:55:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_game *game)
{
	t_philo	*aux;
	size_t	i;

	i = 1;
	aux = game->philo;
	while ((long)i <= game->num_philos)
	{
		if (aux)
		{
			aux = aux->next;
			free(game->philo);
			game->philo = aux;
		}
		i++;
	}
}
