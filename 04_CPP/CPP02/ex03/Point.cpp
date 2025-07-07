/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:17:15 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/07 17:14:41 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

// CANONICAL
Point::Point(void) : _x(0), _y(0) {} //Solo se puede asignar a cero en la lista al ser los dos const.

Point::Point(const Point &point) : _x(point._x), _y(point._y){}

Point &Point::operator=(const Point &point){
	(void)point;
	return (*this);//No se puede desarrollar ya que son const _x e _y
} 

Point::~Point(void){}

//GETTERS
Fixed	Point::getX(void) const{
	return (_x);
}
Fixed	Point::getY(void) const{
	return (_y);
}

//OTRAS FUNCIONES
Point::Point(const float n1, const float n2) : _x(Fixed(n1)), _y(Fixed(n2)){}


