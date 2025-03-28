/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:54:07 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/28 11:07:48 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/ft_printf.h"

int	main(int ac, char **av)
{
	if (ac != 3)
		return (ft_printf("Error:\nNeed: './client PID \"string\"'\n"), 1);
	(void)av;
	return (0);
	
}
