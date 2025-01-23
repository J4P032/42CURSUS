/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:29:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/22 14:32:43 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*returns a substring from 's' starting from 'start' and max length of 'len'*/
/*NULL if not malloc correctly. It has to be "" if start > strlen(s)*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	len_dest;
	char	*dest;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_calloc(1, sizeof(char)));
	len_dest = len_s - start;
	if (len_dest <= 0)
		return (NULL);
	if (len_dest > len)
		len_dest = len;
	dest = (char *)ft_calloc((len_dest + 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s[start], len_dest + 1);
	return (dest);
}
