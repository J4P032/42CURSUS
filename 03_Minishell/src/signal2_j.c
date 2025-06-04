/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2_j.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:21:00 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/04 09:42:25 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	one_hundred_thirty(t_input *input)
{
	write(1, "\n", 1);
	input->last_exit_code = 130;
}

void	one_hundred_thirtyone(t_input *input)
{
	write(1, "Quit (core dumped)\n", 19);
	input->last_exit_code = 131;
}
