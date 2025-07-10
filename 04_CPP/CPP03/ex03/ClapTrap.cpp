/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:26:10 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/10 16:21:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

//CONSTRUCTORES

ClapTrap::ClapTrap(void) : _name(""), _hitPt(10), _maxHitPt(10), _energyPt(10), _attackDmg(0){
	std::cout << GREEN "🔧🥷	Default constructor called" RESET << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitPt(10), _maxHitPt(10), _energyPt(10), _attackDmg(0){
	std::cout << GREEN "🔧🥷	Constructor called for " RESET << name << std::endl;
}

ClapTrap::ClapTrap(std::string name, unsigned int hitPt, unsigned int maxHitPt, unsigned int energyPt, unsigned int attackDmg){
	_name = name;
	_hitPt = hitPt;
	_maxHitPt = maxHitPt;
	_energyPt = energyPt;
	_attackDmg = attackDmg;
	std::cout << CYAN "🔧🥷	ClapTrap constructor called for 'child' " RESET << name << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other){
	std::cout << GREEN "🐑🥷	Copy constructor called for " RESET << other._name << std::endl;
	_name		= other._name;
	_hitPt		= other._hitPt;
	_maxHitPt	= other._maxHitPt;
	_energyPt	= other._energyPt;
	_attackDmg	= other._attackDmg;
}

ClapTrap	&ClapTrap::operator=(const ClapTrap &other){
	std::cout << YELLOW "🟰🥷	Equal operator called for " RESET << other._name << std::endl;
	if (this != &other){
		_name		= other._name;
		_hitPt		= other._hitPt;
		_maxHitPt	= other._maxHitPt;
		_energyPt	= other._energyPt;
		_attackDmg	= other._attackDmg;
	}
	return (*this);
}

//DESTRUCTOR
ClapTrap::~ClapTrap(void){
	std::cout << RED "🧨🥷	Destructor called for " RESET << this->_name << std::endl;
}


//METODOS PUBLICOS
void	ClapTrap::attack(const std::string &target){
	if (!_hitPt){
		std::cout << RED "💀🥷	Unless you believe in life after death ClapTrap " RESET;
		std::cout << _name << "(" << _hitPt << ")" << RED " won't be able to do anything. RIP" RESET << std::endl; 
		return ;
	}
	
	if (_energyPt){
		std::cout << CYAN "⚔️🥷	ClapTrap " RESET << _name << "(" << _hitPt << ")" << CYAN " attacks ";
		std::cout << YELLOW << target << CYAN ", causing " RESET << _attackDmg;
		std::cout << CYAN " points of damage!" RESET << std::endl;
		_energyPt--;
	}
	else{
		std::cout << "💤🥷	ClapTrap " << _name << "(" << _hitPt << ")" << " cannot make the attack to ";
		std::cout << target << " because has 0 energy points." << std::endl;
	}
}

void	ClapTrap::takeDamage(unsigned int amount){
	if (static_cast<int>(amount) < 0){
		std::cout << "------" << std::endl;
		std::cerr << "Error: Negative takeDamage value. Please input in main function positive values. Thanks!" << std::endl;
		std::cout << "------" << std::endl;
		return;
	}
	
	if (!_hitPt){
		std::cout << "💀	"<< _name << "(" << _hitPt << ")" << RED " Don't feel any hit received as it is already DEAD" RESET;
		std::cout << std::endl;
	}
	else{
		if (amount >= _hitPt){
			std::cout << "💀	" << _name << "(" << _hitPt << ")" << RED " receives a final attack of " YELLOW;
			std::cout << amount << RED " points of damage";
			std::cout << " falling dead" RESET << std::endl;
			_hitPt = 0;
		}
		else{
			std::cout << "🤕	" << _name << "(" << _hitPt << ")" << MAGENTA " receives " YELLOW;
			std::cout << amount << MAGENTA " points of damage, leaving him with " GREEN;
			std::cout << _hitPt - amount << MAGENTA " points of life." RESET << std::endl;
			_hitPt -= amount;
		}
	}
}
	
void	ClapTrap::beRepaired(unsigned int amount){
	if (static_cast<int>(amount) < 0){
		std::cout << "------" << std::endl;
		std::cerr << "Error: Negative healing value. Please input in main function positive values. Thanks!" << std::endl;
		std::cout << "------" << std::endl;
		return;
	}
	
	if (!_hitPt){
		std::cout << RED "💀	Could be nice if " RESET << _name << "(" << _hitPt << ")";
		std::cout << RED " could resurrect but, no way!" RESET << std::endl;
		return;
	}
	if (_energyPt){
		std::cout << "⛑️	" << _name << "(" << _hitPt << ")" << GREEN " regain " YELLOW << amount;
		std::cout << GREEN " of points, making him to be at ";
		if (amount + _hitPt >= _maxHitPt){
			_hitPt = _maxHitPt;
			std::cout << "full life again (" << _hitPt << ")" RESET << std::endl;
		}
		else{
			_hitPt += amount;
			std::cout << YELLOW "" << _hitPt << GREEN " points of life" RESET << std::endl;
		}
		_energyPt--;
	}
	else{
		std::cout << "💤	" << _name << " wish he could heal himself but... no energy points to spend" << std::endl;
	}
}

unsigned int	ClapTrap::getDamage(void) const{
	return(_attackDmg);
}

std::string		ClapTrap::getClapName(void) const{
	return (_name);
}

unsigned int	ClapTrap::getHit(void) const{
	return (_hitPt);
}

unsigned int	ClapTrap::getMaxHit(void) const{
	return (_maxHitPt);
}

unsigned int	ClapTrap::getEnergy(void) const{
	return (_energyPt);
}
