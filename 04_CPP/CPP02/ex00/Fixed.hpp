/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:33:04 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/04 18:53:01 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

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

	Fixed(void); 							//canonica constructor
	Fixed(const Fixed &other); 				//canonica copy constructor
	Fixed &operator=(const Fixed &other);	//canonica copy assigment operator
	~Fixed(void); 							//canonica destructor
	

	int		getRawBits(void) const;
	void	setRawBits(int const raw);

	private:
		int					_fixedPointNum;
		static const int	_fractionBits = 8;
};



#endif
