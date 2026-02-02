/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:56:36 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/21 16:17:46 by jrollon-         ###   ########.fr       */
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
void iter(T* array, const size_t len, F f){
	for (size_t i = 0; i < len; i++)
		f(array[i]);		
};

template <typename T>
void printValues(T& element){
	std::cout << GREEN << element << RESET << ", " << std::endl;
	//element++;
};

template <typename T>
void printValues(const T& element){
	std::cout << GREEN << element << RESET << ", " << std::endl;
	std::cout << "CONST" << std::endl;
};

#endif

/*
	El ejercicio no pide que sea una función que se llame igual, pero en mi caso lo he llamado
	igual (overload), lo cual es correcto como función que se pasa const o no const. 
	el tema es que cuando llamamos a la función de esta manera en el main:

	iter(intMatrix, len, printValues<int>); 
	iter(intMatrix, len, printValues<const int>);

	es correcto si solo existe UNA única plantalla llamada "printValues". 
	Pero como en este caso hay dos plantillas sobrecargadas con el mismo nombre, al
	escribir solo printValues<int> o printValues<const int> el compilador no sabe
	qué sobrecarga elegir, porque ambas siguen siendo viables.:

	Veamos las instanciaciones:

	iter(intMatrix, len, printValues<int>); // T = int
		void printValues(T& element){} -> void printValues(int& element){}
		void printValues(const T& element){} -> void printValues(const int& element){}
	
	iter(intMatrix, len, printValues<const int>); T = const int
		void printValues(T& element){} -> void printValues(const int& element){}
		void printValues(const T& element){} -> void printValues(const const int& element){} -> void printValues(const int& element){}
	
	Con uno <int> tendría dos plantillas sobrecargados const y no const y con <const int> 
	tendría las mismas, y por lo tanto todavía habría ambiguedad.
	
	
	y por eso tenemos que castear asi:

	iter(intMatrix, len, static_cast<void(*)(int&)>(printValues)); 
	iter(intMatrix, len, static_cast<void(*)(const int&)>(printValues));

	De esta forma le decimos explícitamente al compilador qué tipo de puntero a función
	queremos (void(int&) o void(const int&)), y eso fuerza a elegir la sobrecarga
	correcta entre las dos plantillas.

	De hecho, esta última forma (con static_cast) también funcionaría incluso si solo
	hubiera una única función (no overloaded).
*/
