
#include "life.h"

void free_it(char** m, int filas){
	for (int f = 0; f < filas; f++){
		if (m && m[f]){
			free(m[f]);
			m[f] = NULL;
		}
	}
	if (m){
		free(m);
		m = NULL;
	}
}



int	print_it(char** m, int	filas, int columnas){
	if (!m)
		return 0;
	
	for (int f = 0; f < filas; f++){
		for (int c = 0; c < columnas; c++){
			putchar(m[f][c]);
		}
		putchar('\n');
	}

	return 1;
}


//./life width height iterations
int	store_data(t_g* g, int ac, char** av){
	(void)ac;
	g->filas = atoi(av[2]);
    g->columnas = atoi(av[1]);
	g->loops = atoi(av[3]);
	g->map = NULL;

	g->map = (char**)calloc(g->filas, sizeof(char*));
	if (!g->map){
		return 0;
	}
	for (int i = 0; i < g->filas; i++){
		g->map[i] = (char*)calloc(g->columnas, sizeof(char));
		if (!g->map[i]){
			for (int j = i - 1; j > -1; j--){
				if (g->map[j]){
					free(g->map[j]);
					g->map[j] = NULL;
				}
			}
			if (g->map){
				free(g->map);
				g->map = NULL;
			}
			return 0;
		}
	}


	g->copia = (char**)calloc(g->filas, sizeof(char*));
	if (!g->copia){
		free_it(g->map, g->filas);
		return 0;
	}
	for (int i = 0; i < g->filas; i++){
		g->copia[i] = (char*)calloc(g->columnas, sizeof(char));
		if (!g->copia[i]){
			for (int j = i - 1; j > -1; j--){
				if (g->copia[j]){
					free(g->copia[j]);
					g->copia[j] = NULL;
				}
			}
			if (g->copia){
				free(g->copia);
				g->copia = NULL;
			}
			free_it(g->map, g->filas);
			return 0;
		}
	}


	for (int f = 0; f < g->filas; f++){
		for (int c = 0; c < g->columnas; c++){
			g->map[f][c] = ' ';
		}
	}
	return 1;
}


void	init_matrix(t_g* g){
	char	c;
	int		fi = 0;
	int		co = 0;
	int		filas = g->filas;
	int		columnas = g->columnas;
	int		writting = 0;
	while (read(0, &c, 1) > 0){
		switch (c){
			case 'w' :
				if (fi > 0)
					fi--;
				break;
			case 'W' :
				if (fi > 0)
					fi--;
				break;
			case 'd' :
				if (co < columnas - 1)
					co++;
				break;
			case 'D' :
				if (co < columnas - 1)
					co++;
				break;
			case 's' :
				if (fi < filas - 1)
					fi++;
				break;
			case 'S' :
				if (fi < filas - 1)
					fi++;
				break;
			case 'a' :
				if (co > 0)
					co--;
				break;
			case 'A' :
				if (co > 0)
					co--;
				break;
			case 'x' :
				writting = !writting;
				break;
			case 'X' :
				writting = !writting;
				break;
			default :
				break;
		}
		if (writting)
			g->map[fi][co] = 'O';
	}

	for (int fil = 0; fil < g->filas; fil++){
		for (int col = 0; c < g->columnas; col++){
			g->copia[fil][col] = g->map[fil][col];
		}
	}
}

int is_inside(t_g* g, int fila, int columna){
	if ((fila >= 0 && fila <= g->filas -1) && (columna >= 0 && columna <= g->columnas - 1))
		return 1;
	return 0;
}


void	modify_it(t_g* g, char** copia, int fila, int columna){
	int	vecinos = 0;
	int vivo = (copia[fila][columna] == 'O') ? 1 : 0;

	for (int f = -1; f < 2; f++){
		for (int c = -1; c < 2; c++){
			if (f == 0 && c == 0)
				continue;
			if (is_inside(g, fila + f, columna + c)){
				if (copia[fila + f][columna + c] == 'O')
					vecinos++;
			}
		}
	}

	if (vivo && (vecinos < 2 || vecinos > 3))
		g->map[fila][columna] = ' ';
	else if (!vivo && vecinos == 3)
		g->map[fila][columna] = 'O';
}


void gol(t_g* g){
	for (int f = 0; f < g->filas; f++){
		for (int c = 0; c < g->columnas; c++){
			g->copia[f][c] = g->map[f][c];
		}
	}

	for (int f = 0; f < g->filas; f++){
		for (int c = 0; c < g->columnas; c++){
			modify_it(g, g->copia, f, c);
		}
	}
}



int	main(int ac, char** av){
	if (ac != 4)
		return 1;

	if (atoi(av[1]) <= 0 || atoi(av[2]) <= 0)
		return 1;

	t_g g;

	if (!store_data(&g, ac, av))
		return 1;
	
	init_matrix(&g);

	for (int i = 0; i < g.loops; i++)
		gol(&g);
		
	print_it(g.map, g.filas, g.columnas);
	
	free_it(g.map, g.filas);
	free_it(g.copia, g.filas);


	return 0;
}