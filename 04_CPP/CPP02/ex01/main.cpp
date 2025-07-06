/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:32:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/06 21:58:02 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"

int main( void ) {
	Fixed a;
	Fixed const b(10);
	Fixed const c(42.42f);
	Fixed const d(b);
	a = Fixed( 1234.4321f );
	
	std::cout << "a is " << a << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;
	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;
	return 0;
}

//Tiene que ser:
/* $> ./a.out
Default constructor called 		-> fixed a;
Int constructor called 			-> Fixed const b(10);
Float constructor called		-> Fixed const c(42.42f);
Copy constructor called			-> Fixed const d(b);
Copy assignment operator called	-> a = Fixed( 1234.4321f );
Float constructor called		-> Fixed( 1234.4321f );
Copy assignment operator called -> _fixedPointNum = other._fixedPointNum;
Destructor called				-> por que es asignado por un temporal Fixed( 1234.4321f ) que al ser asignado se destruye
a is 1234.43
b is 10
c is 42.4219
d is 10
a is 1234 as integer
b is 10 as integer
c is 42 as integer
d is 10 as integer
Destructor called
Destructor called
Destructor called
Destructor called
$ */
