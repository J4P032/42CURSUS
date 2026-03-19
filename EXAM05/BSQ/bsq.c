/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:48:48 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/19 20:07:53 by jrollon-         ###   ########.fr       */
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
	return 1;
}

int copy_map(t_g* m, char* line, int fila){
	int	len;
	int	size;

	size = ft_strlen(line);
	if (line[size - 1] != '\n')
		return 0;
	for (size_t i = 0; i < size; i++){
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
	for (size_t index = 0; index < (size + 2); index++)
		m->map[fila][index] = line[index];
	
	return (1);
}

void	print_map(t_g* m){
	for (size_t f = 0; f < m->lines; f++){
		if (m->map[f])
			fprintf(stdout, "%s", m->map[f]);
	}
}


int main(int ac, char** av){
	FILE 	*stream;
    char 	*line = NULL;
    size_t 	len = 0;
    ssize_t nread;
	int		fila = 0;
	int		arg = (ac == 1) ? 0 : 1;
	t_g		t_map;
	
	
	
	while (arg < ac){
		t_map.map = NULL;
		t_map.columns = 0;
		t_map.lines = 0;
		t_map.error = 0;
		
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
		
		printf("empty: %c\n", t_map.e);
		printf("obsta: %c\n", t_map.o);
		printf("full: %c\n", t_map.f);
		printf("filas: %d\n\n", t_map.lines);
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
       