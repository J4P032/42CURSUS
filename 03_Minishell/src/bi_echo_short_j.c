/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo_short_j.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:24:00 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/17 17:57:08 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	echo_short(t_input *in)
{
	
	/*esta logica funciona para echos lanzados en terminal. no para $kk (echo oculto)*/
	ft_printf("%s", in->parsed);
	if (in->echo_error_n_arg == 1)
		ft_printf("\n");
	
	/* cuando se hace $kk donde kk es echo, el -n viene de la variable. NO
	de el argumento que pasemos como $kk -n
	export kk="echo -nnn -na      msg1    " -> $kk msg2 = -na msg1 msg2(SIN \n)
	export kk="echo msg1" -> $kk -n msg2 = msg1 -n msg2	
	
	no me puedo fiar del in->arg ya que en donde no lo hace no pone -n, pero donde 
	lo hace no lo pone, o sea tengo que buscar el -n en el in->parsed
	TENGO QUE BUSCAR UNA MANERA de cambiar a esta logica cuando el echo venga de una
	variable de entorno... es decir este lanzada por un $VAR
	
	1. cuando se lanza un comando como $ se puede hacer como ''$

	
	*/

	
}
