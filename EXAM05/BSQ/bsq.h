/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:44:13 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/20 11:24:05 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef	struct s_g{
	int		lines;
	char	e;
	char	o;
	char	f;
	int		columns;
	char**	map;
	int		error;
	int		x_sol;
	int		y_sol;
	int		size_sol;
} t_g;


#endif
