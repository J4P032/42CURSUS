/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fire.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:11:01 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/13 16:58:22 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fire.hpp"

Fire::Fire(void) : AMateria("fire"){}

Fire::Fire(const Fire &other) : AMateria(other.getType()){} //podria valer AMateria(other._type) pero mejor usar el getter

Fire::~Fire(void){}

Fire	&Fire::operator=(const Fire &other){
	(void)other; //No se copia por que siempre sera "ice"
	return (*this);
}

AMateria	*Fire::clone(void) const{
	AMateria	*aux = new Fire();
	return (aux);
}

void 		Fire::use(ICharacter &target){
	std::cout << RED "* shoots a ball of fire at " RESET;
	std::cout << target.getName() << RED " *" RESET << std::endl;
}

