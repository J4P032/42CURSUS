/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 09:27:03 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/10 10:49:56 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : ClapTrap("", 100, 100, 50, 20) {
	std::cout << GREEN "⚙️🤖	ScavTrap constructor called" RESET << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name, 100, 100, 50, 20) {
	std::cout << GREEN "⚙️🤖	ScavTrap constructor called for " RESET << name << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other._name, other._hitPt, other._maxHitPt, other._energyPt, other._attackDmg){
	std::cout << GREEN "🐑🤖	ScavTrap copy constructor called for " RESET << other._name << std::endl;
}

ScavTrap::~ScavTrap(void){
	std::cout << RED "🧨🤖	ScavTrap destructor called" RESET << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other){
	if (this != &other){
		ClapTrap::operator=(other);
	}
	std::cout << YELLOW "🟰🤖	ScavTrap equal operator called for " RESET << other._name << std::endl;
	return (*this);
}

void	ScavTrap::attack(const std::string &target){
	if (!_hitPt){
		std::cout << RED "🤖💀	ScavTrap " RESET;
		std::cout << _name << "(" << _hitPt << ")" << RED " is disabled. Won't do anything agains " RESET << target << std::endl; 
		return ;
	}
	
	if (_energyPt){
		std::cout << CYAN "🦾🤖	ScavTrap " RESET << _name << "(" << _hitPt << ")" << CYAN " attacks ";
		std::cout << YELLOW << target << CYAN ", causing " RESET << _attackDmg;
		std::cout << CYAN " points of damage!" RESET << std::endl;
		_energyPt--;
	}
	else{
		std::cout << "💤🤖	ScavTrap " << _name << "(" << _hitPt << ")" << " cannot make the attack to ";
		std::cout << target << " because has 0 energy points." << std::endl;
	}
}

void	ScavTrap::guardGate(void){
	if (_hitPt){
		std::cout << BLUE "🛡️🤖 	ScavTrap " RESET << _name << "(" << _hitPt << ")";
		std::cout << BLUE " is now in Gate keeper mode." RESET << std::endl;
	}
	else{
		std::cout << "💀🤖	 ScavTrap " << _name << "(" << _hitPt << ")" << " is disabled. Cannot enter defense mode" << std::endl;
	}
}


