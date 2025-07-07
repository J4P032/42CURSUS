/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:56:07 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/07 16:43:55 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

#include "Fixed.hpp"

class	Point{
	public:
		//Canonica
		Point(void);
		Point(const Point &point);
		Point &operator=(const Point &point);
		~Point(void);

		//getters
		Fixed	getX(void) const;
		Fixed	getY(void) const;

		//Otras Funciones
		Point(const float n1, const float n2); //constructor
	
	private:
		const Fixed _x;
		const Fixed _y;
};

bool bsp( Point const a, Point const b, Point const c, Point const point);

#endif
