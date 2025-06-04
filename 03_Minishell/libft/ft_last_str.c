/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:32:50 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/22 10:43:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_last_str(t_input *input, char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
		i++;
	if (i > 0)
	{
		update_env(input, "_", str[i - 1]);
		return (str[i - 1]);
	}
	update_env(input, "_", NULL);
	return (NULL);
}
