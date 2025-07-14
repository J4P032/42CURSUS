/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:35:52 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/14 08:44:38 by jrollon-         ###   ########.fr       */
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

void Character::equip(AMateria *m) {
	if (!m)
		return;

	// ¿Ya está en inventario?
	for (size_t j = 0; j < 4; j++) {
		if (_inventory[j] == m)
			return; // Ya está, no hacemos nada
	}

	// Buscar hueco para meterlo
	for (size_t i = 0; i < 4; i++) {
		if (!_inventory[i]) {
			_inventory[i] = m;
			return;
		}
	}

	// No había hueco y no estaba ya -> borrar
	size_t i = 0;
	//ver si esta ya m en el suelo
	while (i < _groundCapacity){
		if (m == _ground[i]){
			return; //salir si esta
		}
		i++;
	}
	//busqueda de hueco en el suelo para dejar el objeto
	i = 0;
	while (i < _groundCapacity && _ground[i]){
		i++;
	}
	if (i < _groundCapacity){
		_ground[i] = m;
	}
	else{//si no hacer hueco nuevo
		AMateria	**aux;
		size_t oldCap = _groundCapacity;
		_groundCapacity += 10;
		aux = new AMateria*[_groundCapacity]; //nueva capacidad aumentada
		
		//copia a aux de _ground y reasignacion
		for (size_t j = 0; j < oldCap; j++){
			aux[j] = _ground[j];
		}
		for (size_t j = oldCap; j < _groundCapacity; j++){
			aux[j] = NULL;
		}
		delete[] _ground;
		_ground = aux;

		//encontrar hueco para el valor no almacenado m
		for (size_t k = 0; k < _groundCapacity; k++) {
        	if (!_ground[k]) {
            	_ground[k] = m;
        		break;
       		}
		}
	}
}

void	Character::unequip(int idx){
	size_t	i = 0;
	
	if (idx < 0 || idx > 3 || !_inventory[idx]){
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
		size_t oldCap = _groundCapacity;
		_groundCapacity += 10;
		aux = new AMateria*[_groundCapacity]; //nueva capacidad aumentada
		
		//copia a aux de _ground y reasignacion
		for (size_t j = 0; j < oldCap; j++){
			aux[j] = _ground[j];
		}
		for (size_t j = oldCap; j < _groundCapacity; j++){
        	aux[j] = NULL;
		}
		delete[] _ground;
		_ground = aux;

		//ahora vaciar el inventario de ese objeto
		i = 0;// busco hueco
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
