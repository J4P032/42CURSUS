/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit_j.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:16:14 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/18 20:33:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

/*with error 1 from too many arguments bash dont exit with 2 yes it does*/
void	exit_miniyo(t_input *in, int num_exit)
{
	if (num_exit == 2)
		ft_printf("miniyo: exit: %s: numeric argument required\n", in->args);
	clean_all(in, num_exit);
	if (num_exit == 0)
		rl_clear_history();
	exit(num_exit);	
}


void	ft_exit(t_input *in)
{
	long long	arg;
	int			error;
	
	error = 0;
	if (in->args[0])
		arg = ft_atol(in->args, &error);
	else
		arg = 0;
	if (error)
		exit_miniyo(in, 2);
	else
	{
		if (!ft_strncmp(in->args, in->parsed, ft_strlen(in->parsed)))
			exit_miniyo(in, arg);
		else
			ft_printf("miniyo: exit: too many arguments\n");
	}
}
