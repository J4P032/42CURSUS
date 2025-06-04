/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env_m.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:24:39 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/05/07 11:02:29 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	print_env(t_input *in, char **envp)
{
	size_t	i;

	if (in->input_split[in->word_after_arg]
		&& in->input_split[in->word_after_arg][0] != '\0')
		printf("env: '%s': No such file or directory\n",
			in->input_split[in->word_after_arg]);
	else
	{
		i = 0;
		while (envp && envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
}

void	ft_env(t_input *in, char **envp)
{
	update_env(in, "_", "/usr/bin/env");
	if (in->args[0] == '-' && in->args[1] && in->args[1] != '-')
		printf("env: invalid option -- '%c'\n", in->args[1]);
	else if (in->args[0] != '\0' && in->args[0] != '-')
		printf("env:'%s': No such file or directory\n", in->args);
	else if (in->args[0] == '-' && in->args[1] == '\0')
	{
		if (in->input_split[in->word_after_arg]
			&& in->input_split[in->word_after_arg][0] != '\0')
			printf("env: '%s': No such file or directory\n",
				in->input_split[in->word_after_arg]);
		else
			return ;
	}
	else if (in->args[2] != '\0')
		printf("env: unrecognized option '%s'\n", in->args);
	else
		print_env(in, envp);
}
