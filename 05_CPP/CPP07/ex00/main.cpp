/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:39:48 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/21 14:56:19 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"

int main( void ) {
	int a = 2;
	int b = 3;
	::swap( a, b );
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;

	//MI EJEMPLO. AL LORO CON ESTE POR EL TEMA DE LValues o RValues
	std::cout << "\n--------- Mi ejemplo ----------" << std::endl;
	float	kk1 = 42.2f, kk2 = 0.4f;
	float* p1 = &kk1, *p2 = &kk2;
	std::cout << "Dir1: " << p1 << " Dir2: " << p2 << std::endl;
	//::swap(&kk1, &kk2); //ver NOTA*
	::swap(p1, p2);
	std::cout << "Dir1: " << p1 << " Dir2: " << p2 << std::endl;
	return 0;
}

/*NOTA*
	si nosotros descomentamos esa linea, nos dará un error el compilador
	diciendo que no puede hacerlo porque &kk1 y &kk2 no son lvalues.
	lvalues son una variable que ha sido definida antes. Por ejemplo:
	
	int x = 42;

	podemos usar x, por que tiene un nombre y podemos obtener su direccion con & 

	un rvalue es algo que definimos no como nombre, temporal:

	5;
	x + 1; // resultado de expresiones tambien es rvalue

	pero en swap yo uso un &kk1 es decir obtener la dirección de memoria de una variable
	lvalue o sea que es un lvalue y estaria bien y no tendría sentido el error de compilación
	que dice que espera un lvalue. 
	La IA cree que es un bug del compilador por que sin la etiqueta CPP98 o Wall Wextra Werror
	sigue dando el error.

	nota2: Luego hablándolo con compañeros, si yo hago un &kk1 y &kk2, aunque venga esa dirección
	de memoria de un float, eso no quiere decir que tenga que saber en tiempo de compilación
	para componer la función que las variables las variables son float*, y por ello debemos
	especificarlas antes de pasarlas qué es lo que son, y por eso funciona con:

	float* p1 = &kk1; etc...
*/
