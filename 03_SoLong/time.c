/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:54:04 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/19 18:11:40 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	delay_time(t_game *game, double time)
{
	double	seconds;
	int		num_c;
	double	start;

	start = 0;
	num_c = game->map->num_c;
	seconds = ((0.01 - time) / 100) * num_c + time;
	if (seconds < 0)
        seconds = 0;
	while (sin(start) < seconds)
		start += 0.0000001;
}

int	scale_time(int *num, int time)
{
	if (*num < 100 * time)
		return (1);
	if (*num > 200 * time && *num < 300 * time)
		return (2);
	if (*num > 300 * time)
	{
		*num = 0;
		return (0);
	}
	return (0);
}

int	only_once(int *num, int time)
{
	if (*num < 100 * time)
		return (1);
	if (*num > 200 * time && *num < 300 * time)
		return (2);
	return (2);
}
