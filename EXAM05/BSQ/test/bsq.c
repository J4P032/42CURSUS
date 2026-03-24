


#include "bsq.h"

int ft_strlen(const char* s){
    int i = 0;
    while (s && s[i])
        i++;
    return (i);
}

int is_digit(char c){
    return (c >= '0' && c <= '9');
}

void	free_matrix(char** m, int lineas){
	for (int i = 0; i < lineas; i++){
		if (m && m[i]){
			free(m[i]);
			m[i] = NULL;
		}
	}
	if (m){
		free(m);
		m = NULL;
	}
}


void	free_all(t_g* g){
	for (int i = 0; i < g->lines; i++){
		if (g->map && g->map[i]){
			free(g->map[i]);
			g->map[i] = NULL;
		}
	}
	if (g->map){
		free(g->map);
		g->map = NULL;
	}
}




void	print_it(char** m, int filas){
	if (!m)
		return;
	for (int i = 0; i < filas; i++){
		if (m[i])
			fprintf(stdout, "%s", m[i]);
	}
}


void    store_data(t_g* g, const char* line){
    //9.ox\n\0
    if (!g)
        return;

    g->map_error = 0;
	g->map = NULL;
	g->lines = 0;

    int data_len = ft_strlen(line);

    if (data_len < 5){
        g->map_error = 1;
        return;
    }
    int digitos = data_len - 4;

    int index = data_len - 1;
    index--;
    if (index >= 0 && line[index] == '\n')
        index--;
   /*
    int		lines;
	char	e;
	char	o;
	char	f;
   */
    g->f = line[index--];
    g->o = line[index--];
    g->e = line[index--];
    
    int dec = 1;
    for (int i = 0; i < digitos; i++){
        if (is_digit(line[index])){
            g->lines += (line[index--] - '0') * dec;
			dec *= 10;
        }
        else{
            g->map_error = 1;
            break;
        }
    }
	if (g->lines < 1)
		g->map_error = 1;
}




int	copy_line(t_g* g, char* line, int linea){
	if (!g->map){
		g->map = (char**)calloc(g->lines, sizeof(char*));
		if (!g->map){
			g->map_error = 1;
			return 0;
		}
	}

	int len = ft_strlen(line);

	if (len != g->columnas){
		g->map_error = 1;
		return 0;
	}
	
	if (len > 0 && line[len - 1] != '\n'){
		g->map_error = 1;
		return 0;
	}

	
	g->map[linea] = (char*)calloc(len + 1, sizeof(char));
	if (!g->map[linea]){
		g->map_error = 1;
		return 0;
	}
	
	for (int i = 0; i < len; i++){
		char c = line[i];

		if (c == g->e || c == g->o || c == g->f || c == '\n')
			g->map[linea][i] = line[i];
		else{
			g->map_error = 1;
			return 0;
		}
	}
	g->map[linea][len] = '\0';
	
	return 1;
}


int main(int ac, char** av){
	int     linea;
    FILE    *stream;
    char*   line = NULL;
    size_t  len = 0;
    ssize_t nread;
    t_g     g;
    
    int     arg = (ac == 1) ? 0 : 1;    
    while (arg < ac){
		linea = 0;
		
        stream = (ac == 1) ? stdin : fopen(av[arg], "r");
        while  ((nread = getline(&line, &len, stream)) != -1){
			if (linea == 0){
				store_data(&g, line);
				if (g.map_error)
				break;
			linea++;
			continue;
		}
		
		//...\n\0 = 4
		if (linea == 1){
			g.columnas = ft_strlen(line);
			if (g.columnas < 1){
				g.map_error = 1;
				break;
			}
		}
		
		if (!copy_line(&g, line, linea - 1)){
			g.map_error = 1;
			break;
		}
		linea++;
	}

	print_it(g.map, g.lines);
	
	free_matrix(g.map, g.lines);

	
	if (ac != 1)
		fclose(stream);

	arg++;
}
	free(line);
/* 	printf("lines: %d\n\n", g.lines);
	printf("f: %c\n", g.f);
	printf("o: %c\n", g.o);
	printf("e: %c\n", g.e); */
	printf("error: %d\n", g.map_error);

	

	return 0;

}