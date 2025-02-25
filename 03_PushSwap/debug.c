/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:02:13 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/25 14:47:57 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void *__wrap_calloc(size_t nmemb, size_t size)
{
	static int j;
	j++;
	if (1 == j)
		return (NULL);

	// Llamada a la función real de calloc
	void *ptr = __real_ft_calloc(nmemb, size);
	return (ptr);
}

