/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 09:03:37 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/10 11:46:02 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(void) : ClapTrap("", 100, 100, 100, 30) {
	std::cout << GREEN "🔧👹	FragTrap constructor called" RESET << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name, 100, 100, 100, 30) {
	std::cout << GREEN "🔧👹	FragTrap constructor called for " RESET << name << std::endl;
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other._name, other._hitPt, other._maxHitPt, other._energyPt, other._attackDmg){
	std::cout << GREEN "🐑👹	FragTrap copy constructor called for " RESET << other._name << std::endl;
}

FragTrap::~FragTrap(void){
	std::cout << RED "🧨👹	FragTrap destructor called" RESET << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &other){
	if (this != &other){
		ClapTrap::operator=(other);
	}
	std::cout << YELLOW "🟰👹	FragTrap equal operator called for " RESET << other._name << std::endl;
	return (*this);
}

void	FragTrap::highFivesGuys(void){
	if (_hitPt){
		std::cout << BLUE "✋👹	FragTrap " RESET << _name << "(" << _hitPt << ")";
		std::cout << BLUE " asks for a high-five to everyone. " RESET << std::endl;
	}
	else{
		std::cout << "💀👹	FragTrap " << _name << "(" << _hitPt << ")" << " is no more with us. Cannot salute people." << std::endl;
	}
}



