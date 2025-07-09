/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:26:10 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/09 10:23:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

//CONSTRUCTORES

ClapTrap::ClapTrap(void){
	std::cout << GREEN "Default constructor called" RESET << std::endl;
	_name		= "";
	_hitPt		= 10;
	_energyPt	= 10;
	_attackDmg	= 0;
}

ClapTrap::ClapTrap(std::string name){
	std::cout << GREEN "Constructor called for " RESET << name << std::endl;
	this->_name = name;
	_hitPt		= 10;
	_energyPt	= 10;
	_attackDmg	= 0;
}

ClapTrap::ClapTrap(std::string name, unsigned int hitPt, unsigned int energyPt, unsigned int attackDmg){
	_name = name;
	_hitPt = hitPt;
	_energyPt = energyPt;
	_attackDmg = attackDmg;
	//no imprimo nada ya que este constructor viene de ScavTrap y no se le llamara en ClapTrap.	
}

ClapTrap::ClapTrap(const ClapTrap &other){
	std::cout << GREEN "Copy constructor called for " RESET << other._name << std::endl;
	_name		= other._name;
	_hitPt		= other._hitPt;
	_energyPt	= other._energyPt;
	_attackDmg	= other._attackDmg;
}

ClapTrap	&ClapTrap::operator=(const ClapTrap &other){
	std::cout << YELLOW "Equal operator called for " RESET << other._name << std::endl;
	if (this != &other){
		_name		= other._name;
		_hitPt		= other._hitPt;
		_energyPt	= other._energyPt;
		_attackDmg	= other._attackDmg;
	}
	return (*this);
}

//DESTRUCTOR
ClapTrap::~ClapTrap(void){
	std::cout << RED "Destructor called for " RESET << this->_name << std::endl;
}


//METODOS PUBLICOS
void	ClapTrap::attack(const std::string &target){
	if (!_hitPt){
		std::cout << RED "Unless you believe in life after death ClapTrap " RESET;
		std::cout << _name << RED " won't be able to do anything. RIP" RESET << std::endl; 
		return ;
	}
	
	if (_energyPt){
		std::cout << CYAN "ClapTrap " RESET << _name << CYAN " attacks ";
		std::cout << YELLOW << target << CYAN ", causing " RESET << _attackDmg;
		std::cout << CYAN " points of damage!" RESET << std::endl;
		_energyPt--;
	}
	else{
		std::cout << "ClapTrap " << _name << " cannot make the attack to ";
		std::cout << target << " because has 0 energy points." << std::endl;
	}
}

void	ClapTrap::takeDamage(unsigned int amount){
	if (!_hitPt){
		std::cout << RED "The enemy hit viciously the corpse of " RESET;
		std::cout << _name << std::endl;
	}
	else{
		if (amount >= _hitPt){
			std::cout << _name << RED " receives a final attack of " YELLOW;
			std::cout << amount << RED " points of damage";
			std::cout << " falling dead with his blank eyes" RESET << std::endl;
			_hitPt = 0;
		}
		else{
			std::cout << MAGENTA "ClapTrap " RESET << _name << MAGENTA " receives " YELLOW;
			std::cout << amount << MAGENTA " points of damage, leaving him with " GREEN;
			std::cout << _hitPt - amount << MAGENTA " points of life." RESET << std::endl;
			_hitPt -= amount;
		}
	}
}
	
void	ClapTrap::beRepaired(unsigned int amount){
	if (!_hitPt){
		std::cout << RED "Guardian Angel of " RESET << _name;
		std::cout << RED " tries to resurrect his client but fairy tales occurs other places." RESET << std::endl;
		return;
	}
	if (_energyPt){
		std::cout << GREEN "ClapTrap " RESET << _name << GREEN " regain " YELLOW << amount;
		std::cout << GREEN " of points, making him to be at ";
		if (amount + _hitPt >= 10){
			std::cout << "full life again (10)" RESET << std::endl;
			_hitPt = 10;
		}
		else{
			_hitPt += amount;
			std::cout << YELLOW "" << _hitPt << GREEN " points of life" RESET << std::endl;
		}
		_energyPt--;
	}
	else{
		std::cout << "ClapTrap " << _name << " wish he could heal himself but... no way" << std::endl;
	}
}


