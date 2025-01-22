/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:27:15 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/22 13:53:15 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Apply the funcion 'f' to each char of string 's'*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s_aux;
	size_t	s_len;
	size_t	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	s_aux = (char *)ft_calloc(s_len + 1, sizeof(char));
	if (!s_aux)
		return (NULL);
	while (i < s_len)
	{
		s_aux[i] = f(i, s[i]);
		i++;
	}
	return (s_aux);
}
