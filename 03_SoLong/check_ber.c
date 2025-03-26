/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ber.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:32:13 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/25 15:59:48 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_ber(char *map_dir)
{
	size_t	len;

	len = ft_strlen(map_dir);
	if (len < 5)
	{
		write(1, "Error\n", 6);
		write(1, "File extension not valid. Only .ber\n", 36);
		exit (1);
	}
	if (ft_strncmp(map_dir + len - 4, ".ber", 4))
	{
		write(1, "Error\n", 6);
		write(1, "File extension not valid. Only .ber\n", 36);
		exit (1);
	}
}
