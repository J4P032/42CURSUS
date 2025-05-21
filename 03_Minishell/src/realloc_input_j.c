/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_input_j.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:13:06 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/21 14:21:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

char	*ft_str_realloc(char *str, size_t num)
{
	char	*new;
	size_t	i;

	i = 0;
	new = (char *)ft_calloc(ft_strlen(str) + num + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (str && str[i])
	{
		new[i] = str[i];
	 	i++;
	}
	if (str)
		free(str);
	return (new);
}

void	dynamic_input(t_input *in, size_t k)
{
	if (in->token && k < in->realloc_counter * 100)
		return ;
	else
	{
		in->realloc_counter++;
		in->token = ft_str_realloc(in->token, 100);
		if (!in->token)
			clean_all(in, 1);
	}
}
