/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:48:48 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/24 17:22:49 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

//#define _GNU_SOURCE

int	is_digit(char c){
	return (c >= '0' && c <= '9');
}

size_t	ft_strlen(char* s){
	if (!s)
		return 0;
	size_t i = 0;
	while (s[i])
		i++;
	return (i);
}

void	free_all(t_g* m){
	if (!m || !m->map)
		return;
	for (int i = 0; i < m->lines; i++){
		if (m->map[i]){
			free(m->map[i]);
			m->map[i] = NULL;
		}
	}
	if (m->map){
		free(m->map);
		m->map = NULL;
	}
}

int	store_data(t_g* m, char* str){
	if (!m)
		return 0;
	
	size_t	i = 0;
	int		digits = 0;
	int 	dec = 1;
	
	i = ft_strlen(str);
	digits = i - 4;
	
	if (i < 5) //se incluye el \n
		return 0;
	i--;
	if (str[i] == '\n' )
		i--;
	
	m->f = str[i--];
	
	m->o = str[i--];
	if (m->o == m->f)
		return 0;
	
	m->e = str[i--];
	if (m->e == m->o || m->e == m->f)
		return 0;
	
	for (int j = 0; j < digits; j++){
		if (!is_digit(str[i]))
			return 0;
		m->lines += (str[i--] - '0') * dec;
		dec *= 10;
	}
	if (m->lines < 1)
		return 0;
	return 1;
}

int copy_map(t_g* m, char* line, int fila){
	int	size;

	if ((fila + 1) > m->lines)
		return 0;
	size = ft_strlen(line);
	if (size > 0 && line[size - 1] != '\n')
		return 0;
	
	for (int i = 0; i < size; i++){
		char _c = line[i];
		if (_c == m->e || _c == m->f || _c == m->o || _c == '\n' || _c == '\0')
			continue;
		return 0;
	}	
	
	size = size - 1;
	if  (size != m->columns){
		return 0;
	}
		
	if (!m->map){
		m->map = (char**)calloc(m->lines, sizeof(char*));
		if (!m->map)
			return (0);
	}
	
	m->map[fila] = (char*)calloc(size + 2, 1); //incluir el /n y el /0
	if (!m->map[fila]){
		free_all(m);
		return 0;
	}
	for (int index = 0; index < (size + 2); index++)
		m->map[fila][index] = line[index];
	
	return (1);
}

void	print_map(t_g* m){
	if (!m || !m->map)
		return;
	for (int f = 0; f < m->lines; f++){
		if (m->map[f])
			fprintf(stdout, "%s", m->map[f]);
	}
}

int fit_hor(t_g* m, int size, int l, int c){
	int contador = 0;
	
	while (contador < size){
		if (m->map[l][c + contador] && m->map[l][c + contador] == m->e)
			contador++;
		else
			break;
	}
	if (contador == size)
		return (1);
	return 0;
}

int	fit(t_g* m, int size, int l, int c){
	if (!m || !m->map)
		return (0);
	int contador = 0;
	
	while (contador < size){
		if (fit_hor(m, size, l + contador, c)){
			contador++;
			continue;
		}
		break;
	}
	if (contador == size)
		return (1);
	return 0;
}

void	bsq_it(t_g* m){
	m->x_sol = -1;
	m->y_sol = -1;
	m->size_sol = -1;
	int	size;
	int	linea;
	int columna;

	if (!m || !m->map)
		return;
	size = (m->lines <= m->columns) ? m->lines : m->columns;
	for (int i = size; i > 0; i--){
		linea = 0;
		columna = 0;
		while (linea < m->lines){
			while (columna < m->columns){
				if (fit(m, i, linea, columna)){
					m->x_sol = columna;
					m->y_sol = linea;
					m->size_sol = i;
					return;
				}
				columna++;
			}
			linea++;
		}
	}
}


void draw_map(t_g* m){
	if (!m || !m->map)
		return;
	int fila = m->y_sol;
	int colu = m->x_sol;
	int size = m->size_sol;
	for (int l = fila; l < fila + size; l++){
		for (int c = colu; c < colu + size; c++){
			m->map[l][c] = m->f;
		}
	} 
}

int main(int ac, char** av){
	FILE 	*stream;
    char 	*line = NULL;
    size_t 	len = 0;
    ssize_t nread;
	int		fila;
	int		arg = (ac == 1) ? 0 : 1;
	t_g		t_map;
	
	while (arg < ac){
		t_map.map = NULL;
		t_map.columns = 0;
		t_map.lines = 0;
		t_map.error = 0;
		fila = 0;
		
		stream = (ac == 1) ? stdin : fopen(av[arg], "r");
		if (stream == NULL)
			t_map.error = 1;
		while ((nread = getline(&line, &len, stream)) != -1) {
			if (fila == 0){
				if (!store_data(&t_map, line)){
					t_map.error = 1;
					break;
				}
				fila++;
				continue;
			}
			if (fila == 1){
				t_map.columns = ft_strlen(line) - 1;
				if (t_map.columns <= 0){
					t_map.error = 1;
					break;
				}
			}
			if (!copy_map(&t_map, line, fila - 1)){
				t_map.error = 1;
				break;
			}
			fila++;
		}
			
		if ((fila - 1) != t_map.lines){
			t_map.error = 1;
		}
		
		printf("empty: %c\n", t_map.e);
		printf("obsta: %c\n", t_map.o);
		printf("full: %c\n", t_map.f);
		printf("filas: %d\n\n", t_map.lines);
		
		if (!t_map.error)
			bsq_it(&t_map);
		
		
		printf("sol_fila: %d\n", t_map.y_sol);
		printf("sol_colu: %d\n", t_map.x_sol);
		printf("sol_size: %d\n", t_map.size_sol);
		
		if (!t_map.error && t_map.size_sol > 0)
			draw_map(&t_map);
		else
			t_map.error = 1;
		
		if (!t_map.error)
			print_map(&t_map);
		else
			fprintf(stderr, "map error\n");
				
		if (line){
			free(line);
			line = NULL;
		}
		if (stream != stdin)
			fclose(stream);
		free_all(&t_map);
		arg++;
	}
	
	
	return(0);
}
       