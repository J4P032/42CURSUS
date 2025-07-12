/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:59:22 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 18:02:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice(void) : AMateria("ice"){}

Ice::Ice(const Ice &other) : AMateria(other.getType()){} //podria valer AMateria(other._type) pero mejor usar el getter

Ice::~Ice(void){}

Ice	&Ice::operator=(const Ice &other){
	(void)other; //No se copia por que siempre sera "ice"
	return (*this);
}

AMateria	*Ice::clone(void) const{
	AMateria	*aux = new Ice();
	return (aux);
}

void 		Ice::use(ICharacter &target){
	std::cout << CYAN "* shoots an ice bolt at " RESET;
	std::cout << target.getName() << CYAN " *" RESET << std::endl;
}


