/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:52:12 by jrollon-          #+#    #+#             */
/*   Updated: 2025/05/29 14:31:17 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*original of libft was with different of \n*/
size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s || !s[0])
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
