/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:24:01 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/11 20:49:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(void) : WrongAnimal(){
	_type = "WrongCat";
	std::cout << "🛠️ 😿	" << GREEN"WrongCat Default Constructor Called" RESET << std::endl;
}

WrongCat::WrongCat(const WrongCat &other) : WrongAnimal(other){
	//_type = other._type;
	std::cout << "🐑 😿	" << GREEN"WrongCat Copy Constructor Called" RESET << std::endl;
}

WrongCat::~WrongCat(void){
	std::cout << "💣😿	" << RED"WrongCat Destructor Called" RESET << std::endl;
}

WrongCat	&WrongCat::operator=(const WrongCat &other){
	if (this != &other){
		_type = other._type;
	}
	return (*this);
}

void	WrongCat::makeSound(void) const{
	std::cout << "📢😿	" << CYAN "Miaaaaaaaaaaaaaauuuuuuuuuuuuu???" RESET << std::endl;
}
