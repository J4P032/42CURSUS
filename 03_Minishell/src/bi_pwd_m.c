/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd_m.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:24:39 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/04/28 11:51:29 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	ft_pwd(char **input)
{
	char	cwd[1024];

	if (input[1] && input[1][0] == '-' && input[1][1])
		printf("pwd: usage: pwd");
	else if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("minishell: pwd");
}
