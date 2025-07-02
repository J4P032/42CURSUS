/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:04:33 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/02 11:03:34 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

/*necesitamos init a NULL myWeapon ya que es creado con direccion en privado*/
HumanB::HumanB(const std::string &name) : _name(name), _myWeapon(NULL){}

HumanB::~HumanB(void){}

void	HumanB::attack(void)
{
	std::cout << this->_name << " attacks with their ";
	if (this->_myWeapon == NULL)
		std::cout << "hands" << std::endl;
	else
		std::cout << this->_myWeapon->getType() << std::endl;
}

/*de esta manera puede ser weapon NULL por que es *myWeapon en privado*/
void	HumanB::setWeapon(Weapon &weapon)
{
	this->_myWeapon = &weapon;
}
