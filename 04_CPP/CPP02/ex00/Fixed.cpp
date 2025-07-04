/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:44 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/04 19:14:03 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void){
	std::cout << GREEN "Default constructor called" RESET << std::endl;
	_fixedPointNum = 0;
}

Fixed::Fixed(const Fixed &other){
	std::cout << YELLOW "Copy constructor called" RESET << std::endl;
	*this = other; //de esta manera aparece el mensaje de Copy Assigment operator called
		//pero podria haber hecho this->_fixedPointNum = other._fixedPointNum; pero no aparecia ningun msg
}

/*si la copia que estamos creando es la misma direccion de memoria que nos pasan (a=a) no copiamos...*/
/*...por que aunque generalmente funcionaria sin el if, si hago liberacion de memoria dentro...*/
/*...de la funcion o asignaciones complejas a = a puede causar problemas como doble liberacion...*/
/*...corrupcion o comportamiento indefinido. Mejor proteger.*/
Fixed &Fixed::operator=(const Fixed &other){
	std::cout << CYAN "Copy assignment operator called" RESET << std::endl;
	if (this != &other){
		_fixedPointNum = other.getRawBits();
	}
	return (*this);
}

Fixed::~Fixed(void){
	std::cout << RED "Destructor called" RESET << std::endl;
}

int	Fixed::getRawBits(void) const{
	std::cout << BLUE "getRawbits member function called" RESET << std::endl;
	return (_fixedPointNum);
}

void	Fixed::setRawBits(int const raw){
	std::cout << MAGENTA "setRawBits member function called" RESET << std::endl;
	_fixedPointNum = raw;
}	

