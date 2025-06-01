/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:08:01 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/10 01:24:38 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strcspn(const char *str1, const char *str2)
{
	size_t		i;
	const char	*p;

	i = 0;
	while (str1[i])
	{
		p = str2;
		while (*p)
		{
			if (str1[i] == *p)
				return (i);
			p++;
		}
		i++;
	}
	return (i);
}
