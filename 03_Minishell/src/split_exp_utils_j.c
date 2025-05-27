/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_exp_utils_j.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:48:26 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/27 13:17:20 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell_m.h"
#include "../inc/minishell_j.h"

/*in split_exp I use status_exp to control if the token came between quotes...*/
/*...but potato"tomato" would be 0 as starts without quotes. that is the...*/
/*...reason I mark it with 0x1F that is invisible and not used.*/
void	remove_control_char(char *string)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!string)
		return ;
	str = string;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 0x1F)
		{
			i++;
			while (str[i] && str[i] != 0x1F)
				string[j++] = str[i++];
			if (str[i] == 0x1F)
				i++;
		}
		else
			string[j++] = str[i++];
	}
	string[j] = '\0';
}
