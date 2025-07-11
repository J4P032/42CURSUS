/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:37:35 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/11 21:05:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(void) : _type("any"){
	std::cout << "🛠️ ❓	" << GREEN"Animal Default Constructor Called" RESET << std::endl;
}

Animal::Animal(const Animal &other) : _type(other._type){
	std::cout << "🐑❓	" << GREEN"Animal Copy Constructor Called" RESET << std::endl;
}

Animal::~Animal(void){
	std::cout << "💣❓	" << RED"Animal Destructor Called" RESET << std::endl;
}

Animal	&Animal::operator=(const Animal &other){
	_type = other._type;
	std::cout << "🟰❓	" << BLUE"Animal = Called" RESET << std::endl;
	return (*this);
}

std::string	Animal::getType(void) const{
	return (_type);
}

void	Animal::makeSound(void) const{
	std::cout << "🔇❓	" << YELLOW "I mute my sound because I am not any type of Animal" RESET << std::endl;
}
