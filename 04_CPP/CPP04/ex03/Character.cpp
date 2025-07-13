/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:35:52 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/13 21:08:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "AMateria.hpp"

Character::Character(void) : _name("noName"){
	for (size_t i = 0; i < 4; i++){
		_inventory[i] = NULL;
	}
	_groundCapacity = 10;
	_ground = new AMateria*[_groundCapacity];
	for (size_t i = 0; i < _groundCapacity; i++){
		_ground[i] = NULL;
	}
}

Character::Character(const std::string &name) : _name(name){
	for (size_t i = 0; i < 4; i++){
		_inventory[i] = NULL;
	}
	_groundCapacity = 10;
	_ground = new AMateria*[_groundCapacity];
	for (size_t i = 0; i < _groundCapacity; i++){
		_ground[i] = NULL;
	}
}

Character::Character(const Character &other) : _name(other.getName()),
	_groundCapacity(other._groundCapacity){
	for (size_t i = 0; i < 4; i++){
		if (other._inventory[i]){
			_inventory[i] = other._inventory[i]->clone(); //copia profunda del objeto
		}
		else{
			_inventory[i] = NULL;
		}
	}
	_ground = new AMateria*[_groundCapacity];
	for (size_t i = 0; i < _groundCapacity; i++){
		if (other._ground[i]){
			_ground[i] = other._ground[i]->clone(); 
		}
		else{
			_ground[i] = NULL;
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
	for (size_t i = 0; i < _groundCapacity; i++){
		if (_ground[i]){
			delete _ground[i];
		}
	}
	delete[] _ground;
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
	//primero vaciar todo el suelo del char ya creado
	for (size_t i = 0; i < _groundCapacity; i++){
		if (_ground[i]){
			delete _ground[i];
		}
	}
	delete[] _ground;
	//ahora copiarlo
	_groundCapacity = other._groundCapacity;
	_ground = new AMateria*[_groundCapacity];
	for(size_t i = 0; i < _groundCapacity; i++){
		if (other._ground[i]){
			_ground[i] = other._ground[i]->clone();
		}
		else{
			_ground[i] = NULL;
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
	size_t	j = 0;
	
	while (i < 4){
		if (!_inventory[i]){
			break;
		}
		i++;
	}
	if (m && i < 4){
		while (j < 4 && m != _inventory[j]){
			j++;
		}
		if (j > 3){
			_inventory[i] = m;
		}
	}
	else{
		j = 0;
		while (j < 4 && m != _inventory[j]){
			j++;
		}
		
		if (j > 3){
			delete m;
		}
	}
}

void	Character::unequip(int idx){
	size_t	i = 0;
	
	if (idx < 0 || idx > 3){
		return;
	}
	//busqueda de hueco en el suelo para dejar el objeto
	while (i < _groundCapacity && _ground[i]){
		i++;
	}
	if (i < _groundCapacity){
		_ground[i] = _inventory[idx]; //asi no habra leak
		_inventory[idx] = NULL;	
	}
	else{
		AMateria	**aux;
		_groundCapacity += 10;
		aux = new AMateria*[_groundCapacity]; //nueva capacidad aumentada
		
		//copia a aux de _ground y reasignacion
		for (size_t j = 0; j < _groundCapacity; j++){
			if ((j < _groundCapacity - 10) && _ground[j]){
				aux[j] = _ground[j]; //no necesito hacer clone ya que deseo conservar el puntero antiguo
			}
			else{
				aux[j] = NULL;
			}
		}
		delete[] _ground;
		_ground = aux;

		//ahora vaciar el inventario de ese objeto
		i = 0; //el i seria uno mas que la capacidad antigua.. pero mejor buscar el NULL
		while (i < _groundCapacity && _ground[i]){
			i++;
		}
		_ground[i] = _inventory[idx]; 
		_inventory[idx] = NULL;	
	}
}

void	Character::use(int idx, ICharacter &target){
	if (idx < 0 || idx > 3){
		return;
	}
	if (_inventory[idx]){
		_inventory[idx]->use(target);
	}
}
