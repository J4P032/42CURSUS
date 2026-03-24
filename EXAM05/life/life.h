/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:14:15 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/24 17:14:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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