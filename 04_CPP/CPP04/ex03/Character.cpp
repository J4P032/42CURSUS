/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:35:52 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 21:20:36 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "AMateria.hpp"

Character::Character(void) : _name("noName"){
	for (size_t i = 0; i < 4; i++){
		_inventory[i] = NULL;
	}	
}

Character::Character(const std::string &name) : _name(name){
	for (size_t i = 0; i < 4; i++){
		_inventory[i] = NULL;
	}
}

Character::Character(const Character &other) : _name(other.getName()){
	for (size_t i = 0; i < 4; i++){
		if (other._inventory[i]){
			_inventory[i] = other._inventory[i]->clone();
		}
		else{
			_inventory[i] = NULL;
		}
	}
}

Character::~Character(void){
	for (size_t i = 0; i < 4; i++){
		if (_inventory[i]){
			delete _inventory[i];
			_inventory[i] = NULL;
		}
	}
}

Character	&Character::operator=(const Character &other){
	if (this == &other){
		return (*this);
	}
	_name = other.getName();
	for (size_t i = 0; i < 4; i++){
		if (other._inventory[i]){
			if (_inventory[i]){
				delete _inventory[i];
			}
			_inventory[i] = other._inventory[i]->clone();
		}
		else{
			if (_inventory[i]){
				delete _inventory[i];
			}
			_inventory[i] = NULL;
		}
	}
	return (*this);
}

//METODOS DEL INTERFACE

std::string const &Character::getName() const{
	return (_name);
}

void	Character::equip(AMateria *m){
	size_t	i = 0;

	while (i < 4){
		if (!_inventory[i]){
			break;
		}
		i++;
	}
	if (m && i < 4){
		_inventory[i] = m;
	}
}

void	Character::unequip(int idx){
	if (idx < 0 || idx > 3){
		return;
	}
	_inventory[idx] = NULL;	//CUIDADO QUE PUEDE HABER LEAK SI NO SE SALVA ANTES LA MATERIA	
}

void	Character::use(int idx, ICharacter &target){
	if (idx < 0 || idx > 3){
		return;
	}
	if (_inventory[idx]){
		_inventory[idx]->use(target);
	}
}
