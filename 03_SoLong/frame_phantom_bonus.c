/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_phantom_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:49:08 by jrollon-          #+#    #+#             */
/*   Updated: 2025/03/22 22:12:30 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	phantom_path_finding(t_game *game)
{
	int	i;
	int	j;

	
	i = game->win->sprite[14].y / SPRITE_HEIGHT;
	j = game->win->sprite[14].x / SPRITE_WIDTH;


	if (game->map_cpy[i][j + 1] == '0')
		game->map_cpy[i][j + 1] = 'g';
	else if (game->map_cpy[i][j - 1] == '0')
		game->map_cpy[i][j - 1] = 'g';
	else if (game->map_cpy[i + 1][j] == '0')
		game->map_cpy[i + 1][j] = 'g';
	else if (game->map_cpy[i - 1][j] == '0')
		game->map_cpy[i - 1][j] = 'g';
	else if (game->map_cpy[i][j + 1] == 'g' || game->map_cpy[i][j - 1] == 'g'
		||	game->map_cpy[i + 1][j] == 'g' || game->map_cpy[i - 1][j] == 'g')
		game->map_cpy[i][j] = 'g';
}

int	phantom_go(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < game->map->lines)
	{
		j = 0;
		while (j < game->map->columns)
		{
			if (game->map_cpy[i][j] == 'g')
			{
				game->win->sprite[14].i = i;
				game->win->sprite[14].j = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}


void	phantom_sprite_anim(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->win->mlx, game->win->win, game->win->sprite[14].img[0].img, x, y);
}


void	phantom_anim(t_game *game)
{
	static int i;
	int	x;
	int	y;

	i++;
	phantom_path_finding(game);
	phantom_go(game);
	x = game->win->sprite[14].j * SPRITE_WIDTH;
	y = game->win->sprite[14].i * SPRITE_HEIGHT;
	if (game->win->sprite[14].x != x && i % 3 == 0)
	{
		if (game->win->sprite[14].x < x)
			game->win->sprite[14].x++;
		else if (game->win->sprite[14].x > x)
			game->win->sprite[14].x--;
	}
	else if (game->win->sprite[14].y != y && i % 3 == 0)
	{
		if (game->win->sprite[14].y < y)
			game->win->sprite[14].y++;
		else if (game->win->sprite[14].y > y)
			game->win->sprite[14].y--;
	}
	phantom_sprite_anim(game, game->win->sprite[14].x, game->win->sprite[14].y);

	for (size_t i = 0; i < game->map->lines; i++) //
	{
		printf("%s", game->map_cpy[i]);//
	}
	printf("\n");//

	///VA POR PAREDES. EL PROBLEMA ES QUE EN CUANTO PASA EL ORIGEN 0,0 DEL FANTASMA A LA OTRA CASILLA, YA CONSIDERA QUE ESTA EN ZONA
	//SIN PAREDES, CUANDO TODAVIA ESTA. HAY QUE IMPLEMENTAR LO MISMO QUE EL PACMAN. EL ORIGINEN +64 EN Y y origen + 64  en X y que sea
	//condicion && las dos.


}	
