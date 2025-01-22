/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:00:15 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/22 18:10:01 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*compare both memory & up to n bytes*/
/*return 0 if are equal || rest s1 - s2 in first different byte*/
/*n = 0 -> return 0  */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	int				found;
	unsigned char	*s1_aux;
	unsigned char	*s2_aux;

	i = 0;
	found = 0;
	if (n == 0)
		return (0);
	s1_aux = (unsigned char *)s1;
	s2_aux = (unsigned char *)s2;
	while ((i < n) && (s1_aux[i] == s2_aux[i]))
	{
		if (s1_aux[i] == s2_aux[i])
			found = i;
		i++;
	}
	if (i == n)
		return ((int)s1_aux[found] - (int)s2_aux[found]);
	else
		return ((int)s1_aux[i] - (int)s2_aux[i]);
}
