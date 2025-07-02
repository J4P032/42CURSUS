/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:04:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/02 11:01:02 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

/*necesita list init pq son una referencia antes de pasar al cuerpo de la funcion*/
/*En myWeapon ya q es una referencia tmb como variable privada.*/
HumanA::HumanA(const std::string &name, Weapon &myWeapon) 
	: _name(name), _myWeapon(myWeapon){}

HumanA::~HumanA(void){}

void	HumanA::attack(void)
{
	std::cout << this->_name << " attacks with their ";
	std::cout << this->_myWeapon.getType() << std::endl;
}
