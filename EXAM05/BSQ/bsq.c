/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:48:48 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/19 14:19:52 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

//#define _GNU_SOURCE

void	store_data(char* str){
	size_t	i = 0;
	while (str)
		i++;
	while (i > -1){
		if (str[i] != ' ')
			continue;
		i--;
	}
}


int main(int ac, char** av){
	FILE 	*stream;
    char 	*line = NULL;
    size_t 	len = 0;
    ssize_t nread;
	int		primera;
	int		arg = (ac == 1) ? 0 : 1;
		
	while (arg < ac){
		primera = 1;
		stream = (ac == 1) ? stdin : fopen(av[arg], "r");
		if (stream == NULL)
			fprintf(stderr, "map error\n");
		while ((nread = getline(&line, &len, stream)) != -1) {
			//fprintf(stdout, "linea: %s", line);
			if (primera){
				store_data(line);
				primera = 0;
			}
			...
		}
		
		if (line){
			free(line);
			line = NULL;
		}
		if (stream != stdin)
			fclose(stream);
		arg++;
	}

	return(0);
}
       