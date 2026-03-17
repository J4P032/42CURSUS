/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 12:33:47 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/17 15:31:22 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_g{
	int		w;
	int		h;
	int		loops;
	char**	tablero; 
	
} t_g;

#endif
