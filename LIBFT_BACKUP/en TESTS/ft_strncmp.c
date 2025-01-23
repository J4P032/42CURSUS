/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:41:07 by jrollon-          #+#    #+#             */
/*   Updated: 2025/01/19 09:57:03 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*Checks if both strings are equal. If they do, it returns a 0, if not it
returns the difference between s1 and s2 in unsigned char ascii code numbers.
n controls up the the size of the string we want to check*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	dif;

	i = 0;
	dif = 0;
	while (((s1[i] != '\0') || (s2[i] != '\0')) && (i < n))
	{
		if ((unsigned char)s1[i] == (unsigned char)s2[i])
			i++;
		else
		{
			dif = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (dif);
		}
	}
	return (0);
}
