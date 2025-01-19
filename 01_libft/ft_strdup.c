/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:57:12 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/19 09:56:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*copies a string to another area of memory (need malloc)*/
/*copy of NULL would be unknown. Returns NULL*/
char	*ft_strdup(const char *s)
{
	size_t			length;
	char			*dest;

	length = ft_strlen(s);
	dest = (char *)ft_calloc(length + 1, sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s, length + 1);
	return (dest);
}
