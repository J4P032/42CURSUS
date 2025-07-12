/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:54:32 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 18:01:51 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure(void) : AMateria("cure"){}

Cure::Cure(const Cure &other) : AMateria(other.getType()){} //podria valer AMateria(other._type) pero mejor usar el getter

Cure::~Cure(void){}

Cure	&Cure::operator=(const Cure &other){
	(void)other; //NO se copia por que siempre sera "Cure"
	return (*this);
}

AMateria	*Cure::clone(void) const{
	AMateria	*aux = new Cure();
	return (aux);
}

void		Cure::use(ICharacter &target){
	std::cout << GREEN "* heals " RESET;
	std::cout << target.getName() << GREEN "'s wounds *" RESET;
	std::cout << std::endl;
}


