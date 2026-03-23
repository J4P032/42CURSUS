#ifndef LIFE_H
# define LIFE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_g{
	int 	filas;
    int 	columnas;
	int		loops;
	char**	map;
	char**	copia;
} t_g; 


#endif