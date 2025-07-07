/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:33:04 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/06 21:20:45 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <climits>
#include <cmath>

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[38;2;255;0;0m"
#define GREEN "\033[38;2;0;255;0m"
#define YELLOW "\033[38;5;226m"
#define BLUE "\033[38;2;0;100;255m"
#define MAGENTA "\033[38;2;100;50;255m"
#define CYAN "\033[38;2;0;200;255m"
#define WHITE "\033[37m"


class	Fixed{
	public:

	Fixed(void);							//canonica constructor
	Fixed(const int	num); 					
	Fixed(const float fnum);
	Fixed(const Fixed &other); 				//canonica copy constructor
	Fixed &operator=(const Fixed &other);	//canonica copy assigment operator
	~Fixed(void); 							//canonica destructor
	
	/*Getters Setters*/
	int		getRawBits(void) const;
	void	setRawBits(int const raw);
	
	/*Member Functions*/
	float	toFloat(void) const;
	int		toInt(void) const;	
	
	//static hace que pertenece a la clase
	//...no al objeto por eso no va implicito this en el primer parametro y se necesita poner...
	//...const en el static es para no modificar en esa referencia el objeto devuelto.
	static Fixed &min(Fixed &lFixed, Fixed &rFixed); 
	static const Fixed &min(const Fixed &lFixed, const Fixed &rFixed);
	static Fixed &max(Fixed &lFixed, Fixed &rFixed);
	static const Fixed &max(const Fixed &lFixed, const Fixed &rFixed);


	/*Overload operators*/
	bool	operator>(const Fixed &rightFixed) const; //const final para no modificar "this"
	bool	operator<(const Fixed &rightFixed) const;
	bool	operator>=(const Fixed &rightFixed) const;
	bool	operator<=(const Fixed &rightFixed) const;
	bool	operator==(const Fixed &rightFixed) const;
	bool	operator!=(const Fixed &rightFixed) const;
	
	Fixed	operator+(const Fixed &rightFixed) const;
	Fixed	operator-(const Fixed &rightFixed) const;
	Fixed	operator*(const Fixed &rightFixed) const;
	Fixed	operator/(const Fixed &rightFixed) const; 

	Fixed	&operator++(void); //++a. &por que debe ser cambiado en el acto. No debe ser const porque lo debe modificar.
	Fixed	operator++(int); //a++. no & por que debe conservar su valor anterior para asignaciones u operaciones antes.
	Fixed	&operator--(void);
	Fixed	operator--(int); //es un dummy el int que permite hacer el a++. Es por convención un int.
	
	
	private:
		int					_fixedPointNum;
		static const int	_fractionBits = 8;
};

std::ostream &operator<<(std::ostream &os, const Fixed &num);

#endif
