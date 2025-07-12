/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:14:02 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 17:17:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria(void) : _type(""){}

AMateria::AMateria(std::string const &type) : _type(type){}

AMateria::AMateria(const AMateria &other) : _type(other._type){}

AMateria::~AMateria(void){}

AMateria &AMateria::operator=(const AMateria &other){
	if (this != &other){
		_type = other._type;
	}
	return (*this);
}

std::string const &AMateria::getType() const{
	return (_type);
}

void AMateria::use(ICharacter &target){}
