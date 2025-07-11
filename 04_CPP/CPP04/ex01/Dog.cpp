/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:06:24 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 00:36:37 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void){
	_type = "Dog";
	_brain = new Brain();
	std::cout << "🛠️ 🐶	" << GREEN"Dog Default Constructor Called" RESET << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other), _brain(new Brain(*other._brain)){
	std::cout << "🐑🐶	" << GREEN"Dog Copy Constructor Called" RESET << std::endl;
}

Dog::~Dog(void){
	delete _brain;
	_brain = NULL;
	std::cout << "💣🐶	" << RED"Dog Destructor Called" RESET << std::endl;
}

Dog	&Dog::operator=(const Dog &other){
	if (this != &other){
		_type = other._type;
		if (_brain){
			delete _brain;
		}
		_brain = new Brain(*other._brain);
	}
	std::cout << "🟰 🐶	" << BLUE"Dog = Called" RESET << std::endl;
	return (*this);
}

void	Dog::makeSound(void) const{
	std::cout << "📢🐕	" << CYAN "Guau! Guaaaau!!" RESET << std::endl;
}
