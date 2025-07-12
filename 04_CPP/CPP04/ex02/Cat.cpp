/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:05:33 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 14:53:57 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Brain.hpp"

Cat::Cat(void){
	_type = "Cat";
	_brain = new Brain();
	std::cout << "🛠️ 😸	" << GREEN"Cat Default Constructor Called" RESET << std::endl;
}

Cat::Cat(const Cat &other) : AAnimal(other), _brain(new Brain(*other._brain)){
 	std::cout << "🐑😸	" << GREEN"Cat Copy Constructor Called" RESET << std::endl;
}

Cat::~Cat(void){
	delete _brain;
	_brain = NULL;
	std::cout << "💣😸	" << RED"Cat Destructor Called" RESET << std::endl;
}

Cat	&Cat::operator=(const Cat &other){
	std::cout << "🟰😸	" << BLUE"Cat = operator Called" RESET << std::endl;
	if (this != &other){
		_type = other._type;
		if (_brain){
			delete _brain;
		}
		_brain = new Brain(*other._brain); //*other._brain porque: 1. other._brain es un puntero
										//y el constructor Brain(const Brain &other) espera una referencia
										//por lo que no puede ser new(other._brain) sino el objeto que es derreferenciando...
										//*other._brain.
	}
	return (*this);
}

void	Cat::makeSound(void) const{
	std::cout << "📢🙀	" << CYAN "Miaaaaaaaaaaaaaauuuuuuuuuuuuu???" RESET << std::endl;
}

Brain	*Cat::getBrain(void) const{
	return (_brain);
}
