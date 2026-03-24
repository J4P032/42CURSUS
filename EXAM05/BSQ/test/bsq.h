#ifndef BSQ_H
# define BSQ_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_g{
	int		lines;
	char	e;
	char	o;
	char	f;

	int		map_error;
	int		columnas;

	char**	map;
	int		l_sol;
	int		c_sol;
	int		s_sol;

}t_g;


#endif