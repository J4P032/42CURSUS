/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:05:33 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/11 21:08:08 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void){
	_type = "Cat";
	std::cout << "🛠️ 😸	" << GREEN"Cat Default Constructor Called" RESET << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other){
 	//_type = other._type;
	std::cout << "🐑😸	" << GREEN"Cat Copy Constructor Called" RESET << std::endl;
}

Cat::~Cat(void){
	std::cout << "💣😸	" << RED"Cat Destructor Called" RESET << std::endl;
}

Cat	&Cat::operator=(const Cat &other){
	std::cout << "🟰😸	" << BLUE"Cat = Called" RESET << std::endl;
	_type = other._type;
	return (*this);
}

void	Cat::makeSound(void) const{
	std::cout << "📢🙀	" << CYAN "Miaaaaaaaaaaaaaauuuuuuuuuuuuu???" RESET << std::endl;
}
