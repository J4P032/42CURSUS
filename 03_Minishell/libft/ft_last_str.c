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

char	*ft_last_str(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
		i++;
	return (str[i]);
}
