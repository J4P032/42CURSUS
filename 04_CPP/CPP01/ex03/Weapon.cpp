/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:03:50 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/02 11:04:05 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(const std::string &myWeapon)
{
	_type = myWeapon;
}

Weapon::~Weapon(void){};

const std::string &Weapon::getType(void) const
{
	return (_type);
}

void Weapon::setType(const std::string &newType)
{
	_type = newType;
}
