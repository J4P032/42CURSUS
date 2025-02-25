/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:57:12 by jrollon-          #+#    #+#             */
/*   Updated: 2025/02/25 14:47:38 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
#define DEBUG_H

#include <stdlib.h>

#ifdef DEBUG
void *__wrap_calloc(size_t nmemb, size_t size);
void *__real_ft_calloc(size_t nmemb, size_t size);  // Declaración correcta
#else
#define __wrap_calloc(nmemb, size) ft_calloc(nmemb, size)
#endif

#endif


