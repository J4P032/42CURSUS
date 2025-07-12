/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:37:35 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 14:56:48 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

AAnimal::AAnimal(void) : _type("any"){
	std::cout << "🛠️ ❓	" << GREEN"Animal Default Constructor Called" RESET << std::endl;
}

AAnimal::AAnimal(const AAnimal &other) : _type(other._type){
	std::cout << "🐑❓	" << GREEN"Animal Copy Constructor Called" RESET << std::endl;
}

AAnimal::~AAnimal(void){
	std::cout << "💣❓	" << RED"Animal Destructor Called" RESET << std::endl;
}

AAnimal	&AAnimal::operator=(const AAnimal &other){
	_type = other._type;
	std::cout << "🟰❓	" << BLUE"Animal = Called" RESET << std::endl;
	return (*this);
}

std::string	AAnimal::getType(void) const{
	return (_type);
}

