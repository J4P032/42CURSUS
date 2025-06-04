/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd_m.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:24:39 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/11 20:52:05 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	ft_pwd(char *args, t_input *input)
{
	char	cwd[1024];
	int		len;

	len = ft_strlen(args);
	if ((args[0] == '-' && args[1] != '-' && args[1])
		|| (args[0] == '-' && args[1] == '-' && len > 2))
	{
		printf("pwd: usage: pwd\n");
		input->last_exit_code = 1;
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		input->last_exit_code = 0;
	}
	else
	{
		perror("miniyo: pwd");
		input->last_exit_code = 1;
	}
}
