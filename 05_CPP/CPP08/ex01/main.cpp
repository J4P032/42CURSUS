/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 10:40:33 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/12 15:37:27 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <ctime>
#include <cstdlib>

//rand solo saca positivos. Tengo que forzarle a transformarlo en negativos con otro rand
void	fill_vector(std::vector<int>& v, size_t n){
		int num;
		int neg;
		for (size_t i = 0; i < n; ++i){
			num = std::rand(); //de 0 a 2147483647
			neg = std::rand();
			if (neg % 2 != 0)
				num = (num * -1) - 1; //-1 para llegar al -2147483648
			v.push_back(num);
		}
}


int	main(void){
	try{
		
		//prueba de extremos
		std::cout << "----- TEST of borders a(5)  ----" << std::endl;
		Span a(5);
		a.addNumber(2147483647);
		a.addNumber(0);
		a.addNumber(-2147483648);
		
		std::cout << a << std::endl;
		std::cout << "Longest Span of a(5): " << a.longestSpan() << std::endl;
		std::cout << "Shortest Span of a(5): " << a.shortestSpan() << std::endl;
		
		//prueba con 10 numeros para ver si lo hace bien. Los imprimo para comprobarlo
		std::cout << std::endl << "----- TEST WITH 10 ints b(10) ----" << std::endl;
		Span b(10);
		//b.addNumber(2); //si descomento este debe dar error de no suficiente espacio
		std::srand(std::time(NULL)); //semilla
		std::vector<int> aux;
		fill_vector(aux, 10);
		b.addNumber(aux.begin(), aux.end()); 
		std::cout << b << std::endl;
		std::cout << "Longest Span of b(10): " << b.longestSpan() << std::endl;
		std::cout << "Shortest Span of b(10): " << b.shortestSpan() << std::endl;
	
		//prueba de union de a y b
		std::cout << std::endl << "----- TEST WITH 10 ints but with join with a(5) ----" << std::endl;
		Span c(10);
		Span d;
		aux.clear();
		fill_vector(aux, 7); //a ya tiene 3 o sea que solo genero 7.
		c.addNumber(aux.begin(), aux.end());
		std::cout << "a(5):" << std::endl;
		std::cout << a << std::endl;
		std::cout << "c(7):" << std::endl;
		std::cout << c << std::endl;
		std::cout << "d(0):" << std::endl;
		std::cout << d << std::endl;
		std::cout << "d = a + c:" << std::endl;
		d = a + c;
		std::cout << d << std::endl;
		std::cout << "Longest Span of d(10): " << d.longestSpan() << std::endl;
		std::cout << "Shortest Span of d(10): " << d.shortestSpan() << std::endl; 
	
		//PRUEBA CON 10000
		std::cout << std::endl << "----- TEST WITH 25000 e(25000) ----" << std::endl;
		Span e(25000);
		aux.clear();
		fill_vector(aux, 25000); 
		e.addNumber(aux.begin(), aux.end());
		std::cout << "Longest Span of e(25000): " << e.longestSpan() << std::endl;
		std::cout << "Shortest Span of e(25000): " << e.shortestSpan() << std::endl;
	
		//fallo de suma con reserva mayor a la permitida
		std::cout << std::endl << "----- TEST exceed of operator+ ----" << std::endl;
		Span uno(3000000000U);
        Span otro(2000000000U);
		Span masotro = uno + otro;
		std::cout << "END OF PROGRAM" << std::endl;
	}
	catch (std::exception& ex){
		std::cout << "Error(exception): " << ex.what() << std::endl;
	}
	return (1);
}
