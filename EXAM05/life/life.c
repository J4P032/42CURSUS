/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 12:37:11 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/17 17:06:00 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	init_game(t_g* g, char** v){
	int x;
	int y;
	g->w = atoi(v[1]);
	g->h = atoi(v[2]);
	x = g->w;
	y = g->h;
	g->loops = atoi(v[3]);
	g->tablero = (char**)malloc(y * sizeof(char*));
	for (size_t i = 0; i < y; i++)
		g->tablero[i] = (char*)malloc(x);
	for (size_t i = 0; i < y; i++){
		for(size_t j = 0; j < x; j++)
			g->tablero[j][i] = '.';
	}	
}

void	start_it(t_g* g){
	char	c;
	size_t	x = 0;
	size_t	y = 0;
	size_t	alto = g->h;
	size_t	ancho = g->w;
	int		writting = 0;
	
	while (read(0, &c, 1) > 0){
		switch (c){
			case 'w' :
				if (y > 0)
					y--;
				break ;
			case 's' :
				if (y < alto - 1)
					y++;
				break ;
			case 'd' :
				if (x < ancho - 1)
					x++;
				break ;
			case 'a' :
				if (x > 0)
					x--;
				break ;
			case 'x' :
				writting = !writting;
			default :
				break ;
		}
		if (writting)
			g->tablero[x][y] = '0';
	}
}

void	print(t_g* g){
	for (size_t i = 0; i < g->h; i++){
		for(size_t j = 0; j < g->w; j++)
			putchar(g->tablero[j][i]);
		putchar('\n');
	}	
}

int	is_inside(t_g* g, int x, int y){
	if (x >= 0 && x <= g->w - 1 && y >= 0 && y <= g->h - 1) 
		return 1;
	return 0; 
}



void	modify_it(t_g* g, char** copia, size_t i, size_t j){
	int x = j;
	int y = i;
	int vivo = 0;
	int	vecinos = 0;

	if (g->tablero[j][i] == 'O')
		vivo = 1;
	
	x--;
	y--;
	
	for (size_t i = 0; i < 3; i++){	
		for (size_t j = 0; j < 3; j++){
			if (is_inside(g, x, y)){
				if (copia[x][y] == 'O' && x != j && y != i)
					vecinos++;
			}
			x++;
		}
		y++;
	}
	if (vivo){
		if (vecinos < 2 || vecinos > 3)
			g->tablero[j][i] = ' ';
	}
	else if (vecinos == 3)
		g->tablero[j][i] = 'O';
		
}	


void game_of_life(t_g* g){
		int	x = g->w;
		int	y = g->h;
		char **copia;
		copia = (char**)malloc(y * sizeof(char*));
		for (size_t i = 0; i < y; i++)
			copia[i] = (char*)malloc(x);
		
		for (size_t i = 0; i < y; i++){
			for (size_t j = 0; j < x; j++)
				copia[j][i] = g->tablero[j][i];
		}
		
		for (size_t i = 0; i < y; i++){
			for (size_t j = 0; j < x; j++)
				modify_it(g, copia, i, j);
		}
		
}



void	free_all(t_g* g){
	for (size_t i = 0; i < g->h; i++)
		free(g->tablero[i]);
	free(g->tablero);
}


int main(int ac, char** av){
		
	if (ac != 4)
		return 1;
	t_g	g;

	
	
	init_game(&g, av);
	start_it(&g);
	print(&g);
	for (size_t i = 0; i < g.loops; i++)
		game_of_life(&g);
	
	
	print(&g);

	free_all(&g);
	return 0;
}
