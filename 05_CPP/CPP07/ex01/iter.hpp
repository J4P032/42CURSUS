/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:56:36 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/20 11:30:25 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

# include <iostream>

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[38;2;255;0;0m"
#define GREEN "\033[38;2;0;255;0m"
#define YELLOW "\033[38;5;226m"
#define BLUE "\033[38;2;0;100;255m"
#define MAGENTA "\033[38;2;100;50;255m"
#define CYAN "\033[38;2;0;200;255m"
#define WHITE "\033[37m"

/* hacemos macro a F tambien para pasarle ambas funciones y construirla dependiendo
que tipo de parametros le pasamos, const o no const. Si no habria que separarlo tambien:

template <typename T> void iter(T *array, const size_t len, void(*f)(T&)) //NoConst
template <typename T> void iter(T *array, const size_t len, void(*f)(T const&)) //para Const

Es decir hacer overload de las dos funciones, pero es mejor lo de abajo declarado
por que abarcas todo en uno. */
template <typename T, typename F>
void iter(T*, const size_t, F);

template <typename T>
void printValues(T&);

template <typename T>
void printValues(const T&);

#endif
