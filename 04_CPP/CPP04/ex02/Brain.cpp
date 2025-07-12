/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:16:08 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 12:09:05 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain(void){
	for (size_t	i = 0; i < 100; i++){
		_ideas[i] = "blank";
	}
	std::cout << "🛠️ 🧠	" << GREEN "Brain default constructor called." RESET << std::endl;
}

Brain::Brain(const Brain &other){
	for (size_t	i = 0; i < 100; i++){
		_ideas[i] = other._ideas[i];
	}
	std::cout << "🐑🧠	" << GREEN "Brain copy constructor called." RESET << std::endl;
}

Brain::Brain(std::string type){
	for (size_t	i = 0; i < 100; i++){
		_ideas[i] = type;
	}
	std::cout << "🛠️ 🧠	" << GREEN "Brain parameter constructor called." RESET << std::endl;
}

Brain::~Brain(void){
	std::cout << "💣🧠	" << RED "Brain destructor called." RESET << std::endl;
}

Brain	&Brain::operator=(const Brain &other){
	if (this != &other){
		for (size_t	i = 0; i < 100; i++){
			_ideas[i] = other._ideas[i];
		}
	}
	std::cout << "🟰🧠	" << BLUE "Brain = OPERATOR called." RESET << std::endl;
	return (*this);
}

//METHODS

std::string	Brain::getIdeas(size_t	index) const{
	if (index < 100){
		return (_ideas[index]);
	}
	return ("blank");
}

void	Brain::setIdeas(size_t index, const std::string &idea){
	if (index < 100){
		_ideas[index] = idea;
	}
}

