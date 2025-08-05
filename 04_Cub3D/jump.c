/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:12:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/08/05 16:21:22 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	jump(t_game *game)
{
	int			jumping;

	jumping = 300;
	RAY.walking_height = jumping * fabs(sin(PI * RAY.i_walking));
	RAY.i_walking += 0.005;
	if (RAY.i_walking >= 1)
	{
		PLAYER.jumping = 0;
		RAY.walking_height = 0;
	}
}
