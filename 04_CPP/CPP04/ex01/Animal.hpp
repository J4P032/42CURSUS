/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:27:24 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/11 23:39:49 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <string>
#include <iostream>
#include <cstdlib> //system("clear")

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[38;2;255;0;0m"
#define GREEN "\033[38;2;0;255;0m"
#define YELLOW "\033[38;5;226m"
#define BLUE "\033[38;2;0;100;255m"
#define MAGENTA "\033[38;2;100;50;255m"
#define CYAN "\033[38;2;0;200;255m"
#define WHITE "\033[37m"

class	Animal{
	protected:
		std::string _type;
	
	public:
		Animal(void);
		Animal(const Animal &other);
		Animal	&operator=(const Animal &other);
		virtual ~Animal(void);

		std::string		getType(void) const; 	//ha de ser const por main pasado
		virtual void	makeSound(void) const; 	//No puede ser pura (=0) por que en el main tenemos 
												//const Animal* meta = new Animal(); Y ESO es IMPOSIBLE en abstracto
};

#endif
