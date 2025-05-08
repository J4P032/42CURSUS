/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo_dollar_j.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 00:12:44 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/09 00:13:23 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

void	manage_dollar(t_input *in, size_t w, int spaced)
{
	size_t	i;
	size_t	j;
	size_t	dollars;
	int		env_n;
	size_t	idollar;//

	i = 0;
	dollars = 0;
	
	while (in->input_split[w][i] != '$')
		i++;
	idollar = i;
	while (in->input_split[w][i] == '$')
	{
		dollars++;
		i++;
	}
	env_n = valid_env((in->input_split[w] + i), in, w);	
		
	if (env_n < 0 && (ft_isalpha(in->input_split[w][i]) || in->input_split[w][i] == '_') && !idollar && is_quoted(in, w) != 2 && dollars == 1)
		;
	else if (spaced)
		printf(" ");
	
	
	i = 0;
	dollars = 0;
	while (in->input_split[w][i])
	{
		if (in->input_split[w][i] != '$')
			printf("%c", in->input_split[w][i]);
		else
		{
			while (in->input_split[w][i + 1] == '$')
			{
				i++;
				dollars++;
			}
			idollar = i + 1;//
			env_n = valid_env((in->input_split[w] + i + 1), in, w);
			if (env_n > -1)
			{
				if (!(dollars % 2))
				{
					j = 0;
					while (in->envp[env_n][j] != '=')
						j++;
					printf("%s", (in->envp[env_n] + j + 1));
				}
				else
				{
					while (in->input_split[w][i] && in->input_split[w][i + 1] != ' ')
					{
						i++;
						printf("%c", in->input_split[w][i]);
					}
				}
			}
			if (in->input_split[w][i])
				i++;
			while (in->input_split[w][i] && in->input_split[w][i + 1] != ' ' && in->input_split[w][i] != '$')
			{
				if (dollars > 0 && (dollars % 2))
					printf("%c", in->input_split[w][i]);
				i++;
			}
			if (env_n < 0 && (ft_isalpha(in->input_split[w][idollar]) || in->input_split[w][idollar] == '_'))
				;
			else if (env_n < 0 && !(dollars % 2))
				printf("$");
		}
		if (in->input_split[w][i] && in->input_split[w][i] != '$')
			i++;
	}		
} 
