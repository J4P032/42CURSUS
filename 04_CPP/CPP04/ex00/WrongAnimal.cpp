/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:21:15 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/11 20:45:09 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void) : _type(""){
	std::cout << "🛠️	" << GREEN"WrongAnimal Default Constructor Called" RESET << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &other) : _type(other._type){
	std::cout << "🐑	" << GREEN"WrongAnimal Copy Constructor Called" RESET << std::endl;
}

WrongAnimal::~WrongAnimal(void){
	std::cout << "💣	" << RED"WrongAnimal Destructor Called" RESET << std::endl;
}

WrongAnimal	&WrongAnimal::operator=(const WrongAnimal &other){
	_type = other._type;
	return (*this);
}

std::string	WrongAnimal::getType(void) const{
	return (_type);
}

void	WrongAnimal::makeSound(void) const{
	std::cout << "🔇	" << YELLOW "I mute my sound because I am not any type of WrongAnimal" RESET << std::endl;
}
