/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:20:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/07 16:59:01 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"

/*bsp significa: Binary Space Partitioning, que se basa en la orientacion...
...de los vectores.
Dado tres puntos A, B, C y un punto P. Se calcula el signo del producto vectorial...
...entre vectores.
AB x AP
BC x BP
CA x CP
Si todos los signos son iguales el punto esta dentro del borde.
Si alguno de los signos son cero el punto esta en el borde
Si los signos no son iguales esta fuera.
la formula: para A(x1,y1), B(x2,y2), P(x,y)

valor = (x2 - x1)*(y - y1) - (y2 - y1)*(x - x1)
valor > 0 -> P esta a la izquierda del vector AB
valor < 0 -> P esta a la derecha
valor = 0 -> P esta sobre la linea 

Se podria hacer por area tambien, en donde se calcula el area que forma P con los...
...otros 3 puntos y si es igual la suma de los tres triangulos al triangulo origen...
...entonces esta dentro. Si es igual y algun triangulo es cero, entonces esta en linea
...y si es mayor la suma, esta fuera. Pero tiene problemas de redondeo.
*/
bool bsp( Point const a, Point const b, Point const c, Point const point){
	Fixed	x1 = a.getX();
	Fixed	y1 = a.getY();
	Fixed	x2 = b.getX();
	Fixed	y2 = b.getY();
	Fixed	x3 = c.getX();
	Fixed 	y3 = c.getY();
	Fixed	x = point.getX();
	Fixed	y = point.getY();

	Fixed	sign1 = (x2 - x1)*(y - y1) - (y2 - y1)*(x - x1); //AB x AP
	Fixed	sign2 = (x3 - x2)*(y - y2) - (y3 - y2)*(x - x2); //BC x BP
	Fixed	sign3 = (x1 - x3)*(y - y3) - (y1 - y3)*(x - x3); //CA x CP

	if (sign1 > 0 && sign2 > 0 && sign3 > 0){
		return (true);
	}
	else if (sign1 == 0 || sign2 == 0 || sign3 == 0){
		return (false);
	}
	else if (sign1 < 0 && sign2 < 0 && sign3 < 0){
		return (true);
	}
	return (false);
}
