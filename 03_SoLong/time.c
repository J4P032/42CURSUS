/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:54:04 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/18 13:32:01 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	scale_time(int *num, int time)
{
	if (*num < 100 * time)
		return (1);
	if (*num > 200 * time && *num < 300 * time)
		return (2);
	if (*num == 300 * time)
	{
		*num = 0;
		return (0);
	}
	return (0);
}
