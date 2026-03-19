/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 12:37:11 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/19 11:35:49 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"


/*en el subject se come en la salida los espacios al principio y si hay dos espacios
seguido o más solo pone uno. Eso sería alterar el print, pero como en una de las
pruebas aparece un 42 precioso, pues prefiero dejarlo como está ya que supongo
que al final no será quitando dichos espacios.*/
int	init_game(t_g* g, char** v){
	int x;
	int y;
	g->w = atoi(v[1]);
	g->h = atoi(v[2]);
	x = g->w;
	y = g->h;
	g->loops = atoi(v[3]);
	g->tablero = (char**)malloc(y * sizeof(char*));
	if (!g->tablero)
		return (0);
	for (size_t i = 0; i < y; i++){
		g->tablero[i] = (char*)malloc(x);
		if (!g->tablero[i]){
			for (int j = i - 1; j > -1; j--)
				free(g->tablero[j]);
			free(g->tablero);
			return (0);
		}
	}
	for (size_t i = 0; i < y; i++){
		for(size_t j = 0; j < x; j++)
			g->tablero[i][j] = ' ';
	}
	return (1);	
}

void	start_it(t_g* g){
	char	c;
	size_t	columna = 0;
	size_t	fila = 0;
	size_t	alto = g->h;
	size_t	ancho = g->w;
	int		writting = 0;
	
	while (read(0, &c, 1) > 0){
		switch (c){
			case 'w' :
				if (fila > 0)
					fila--;
				break ;
			case 's' :
				if (fila < alto - 1)
					fila++;
				break ;
			case 'd' :
				if (columna < ancho - 1)
					columna++;
				break ;
			case 'a' :
				if (columna > 0)
					columna--;
				break ;
			case 'x' :
				writting = !writting;
			default :
				break ;
		}
		if (writting)
			g->tablero[fila][columna] = 'O';
	}
}

void	print(t_g* g){
	for (size_t f = 0; f < g->h; f++){
		for(size_t co = 0; co < g->w; co++)
			putchar(g->tablero[f][co]);
		putchar('\n');
	}	
}

void	print_matrix(char** m, int x, int y){
	for(size_t i = 0; i < y; i++){
		for(size_t j = 0; j < x; j++)
			putchar(m[j][i]);
		putchar('\n');
	}
}

int	is_inside(t_g* g, int x, int y){
	if (x >= 0 && x <= g->w - 1 && y >= 0 && y <= g->h - 1) 
		return 1;
	return 0; 
}

void	modify_it(t_g* g, char** copia, size_t i, size_t j){
	int vivo = 0;
	int	vecinos = 0;

	if (copia[j][i] == 'O')
		vivo = 1;
	
	 for (int f = -1; f <= 1; f++){	
		for (int c = -1; c <= 1; c++){
			if (f == 0 && c == 0)
				continue;

			int	check_x = j + c;
			int check_y = i + f;
			if (is_inside(g, check_x, check_y)){
				if (copia[check_x][check_y] == 'O')
					vecinos++;
			}
		}
	}
	if (vivo){
		if (vecinos < 2 || vecinos > 3)
			g->tablero[j][i] = ' ';
	}
	else if (vecinos == 3)
		g->tablero[j][i] = 'O';
}	

void	free_matrix(char** matrix, int filas){
	for (int f = 0; f < filas; f++ ){
		if (matrix[f]){
			free(matrix[f]);
			matrix[f] = NULL;
		}
	}
	if (matrix){
		free(matrix);
		matrix = NULL;
	}
}

void game_of_life(t_g* g){
		int	columna = g->w;
		int	fila = g->h;
		char **copia;
		copia = (char**)malloc(fila * sizeof(char*));
		for (size_t i = 0; i < fila; i++)
			copia[i] = (char*)malloc(columna);
		
		for (size_t i = 0; i < fila; i++){
			for (size_t j = 0; j < columna; j++)
				copia[j][i] = g->tablero[j][i];
		}
		for (size_t i = 0; i < fila; i++){
			for (size_t j = 0; j < columna; j++)
				modify_it(g, copia, i, j);
		}
		free_matrix(copia, fila);
}

int main(int ac, char** av){
		
	if (ac != 4)
		return 1;
	if (atoi(av[1]) == 0 || atoi(av[2]) == 0)
		return 0; //si es cero reservaria memoria y no sería liberada.
	t_g	g;

	if (!init_game(&g, av))
		return 1;
	start_it(&g);
	for (size_t i = 0; i < g.loops; i++)
		game_of_life(&g);
	print(&g);
	free_matrix(g.tablero, g.h);
	return 0;
}
