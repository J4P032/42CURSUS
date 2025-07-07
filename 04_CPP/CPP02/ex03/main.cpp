/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:32:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/07 17:32:36 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"
#include "Point.hpp"

int main( void ) {

	Point	a(0.0f, 0.0f);
	Point	b(4.5f, 0.0f);	
	Point	c(2.0f, 4.8f);
	
	Point	d(0.0f, 0.0f);
	Point	e(2.0f, 0.0f);	
	Point	f(4.0f, 0.0f); //triangulo todos en linea

	
	Point	point1(2.1f, 1.3f); //esta dentro
	Point	point2(1.5f, 0.0f); //en borde
	Point	point3(4.4f, 4.5f); //fuera
	Point	point4(0.0f, 0.0f); //en vertice
	Point	point5(6.0f, 0.0f); //Alineado con AB pero fuera	
	Point	point6(2.0f, 0.004f); //muy cerca de borde pero dentro

	Point	point7(2.0f, 0.0f); //en misma linea que el triangulo todos el linea

	
	if (bsp(a, b, c, point1)){
		std::cout << "Point1 is inside the triangle" << std::endl;
	}
	else{
		std::cout << "Point1 is NOT inside the triangle" << std::endl;
	}
	
	if (bsp(a, b, c, point2)){
		std::cout << "Point2 is inside the triangle" << std::endl;
	}
	else{
		std::cout << "Point2 is NOT inside the triangle" << std::endl;
	}
	
	if (bsp(a, b, c, point3)){
		std::cout << "Point3 is inside the triangle" << std::endl;
	}
	else{
		std::cout << "Point3 is NOT inside the triangle" << std::endl;
	}

	//************************************ */

	if (bsp(a, b, c, point4)){
		std::cout << "Point4 is inside the triangle" << std::endl;
	}
	else{
		std::cout << "Point4 is NOT inside the triangle" << std::endl;
	}
	
	if (bsp(a, b, c, point5)){
		std::cout << "Point5 is inside the triangle" << std::endl;
	}
	else{
		std::cout << "Point5 is NOT inside the triangle" << std::endl;
	}
		
	if (bsp(a, b, c, point6)){
		std::cout << "Point6 is inside the triangle" << std::endl;
	}
	else{
		std::cout << "Point6 is NOT inside the triangle" << std::endl;
	}

	if (bsp(d, e, f, point7)){
		std::cout << "Point7 is inside the triangle" << std::endl;
	}
	else{
		std::cout << "Point7 is NOT inside the triangle" << std::endl;
	}
	
	return (0);
}
