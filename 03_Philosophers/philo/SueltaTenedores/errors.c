/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:00:33 by jrollon-          #+#    #+#             */
/*   Updated: 2025/04/17 21:43:56 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_errors(int argc, t_game *game, int error, int option)
{
	if ((argc < 5 || argc > 6) && option)
	{
		printf("RUN: ./philo num1 num2 num3 num4 (optional num5)\n");
		printf("num1: Number of philosophers. Maximun = %d.\n", PHILOS_MAX);
		printf("num2: Time(ms) that can survive without eating.\n");
		printf("num3: Time(ms) that they need to finish eating.\n");
		printf("num4: Time(ms) that they sleep.\n");
		printf("num5: Number each philosopher must eat to finish simulation\n");
		return (1);
	}
	else if (!option)
	{
		if (game->num_philos < 1 || game->num_philos > PHILOS_MAX)
			printf("Error: Please num of Philos between 1-%d.\n", PHILOS_MAX);
		if (error && argc == 6)
			printf("Error: Checkout last argument (valid LONG number)\n");
	}
	return (0);
}
