/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:41:48 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/10 17:21:46 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"


DiamondTrap::DiamondTrap(void) : ClapTrap("_clap_name"), ScavTrap() {
	_name = "";
	_hitPt = 100;
	_maxHitPt = 100;
	_energyPt = 50;
	_attackDmg = 20;
	std::cout << GREEN "⚙️💎	DiamondTrap void constructor called" RESET << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"){
	_name = name;
	_hitPt = 100;
	_maxHitPt = 100;
	_energyPt = 50;
	_attackDmg = 20;
	std::cout << GREEN "⚙️💎	DiamondTrap name constructor called" RESET << std::endl;
}
DiamondTrap::DiamondTrap(const DiamondTrap &other) : ClapTrap(other._name + "_clap_name"){
	_name = other._name;
	_hitPt = 100;
	_maxHitPt = 100;
	_energyPt = 50;
	_attackDmg = 20;
	std::cout << GREEN "🐑💎	DiamondTrap Copy constructor called" RESET << std::endl;
}
DiamondTrap::~DiamondTrap(void){
	std::cout << RED "🧨💎	Destructor called for " RESET << this->_name << std::endl;
}
DiamondTrap	&DiamondTrap::operator=(const DiamondTrap &other){
	if (this != &other){
	ClapTrap::_name = other._name + "_clap_name";
		_name = other._name;
		_hitPt = 100;
		_maxHitPt = 100;
		_energyPt = 50;
		_attackDmg = 20;
	}
	std::cout << GREEN "🟰💎	DiamondTrap equal operator called" RESET << std::endl;
	return (*this);
}

std::string	DiamondTrap::getName(void) const{
	return (this->_name);
}
std::ostream	&operator<<(std::ostream &out, const DiamondTrap &r){
	out << "_name: " << r.getName()
		<< " | Clap_name: " << r.ClapTrap::getClapName()
		<< " | MaxHitPt: " << r.getMaxHit()
		<< " | hitPt: " << r.getHit()
		<< " | energyPt: " << r.getEnergy()
		<< " | attackDmg: " << r.getDamage();
	return (out);
}

void	DiamondTrap::whoAmI(){}

