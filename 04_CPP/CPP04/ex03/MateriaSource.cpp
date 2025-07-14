/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:03:29 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/14 08:38:21 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Fire.hpp"

MateriaSource::MateriaSource(void){
	for (size_t i = 0; i < 4; i++){
		_materias[i] = NULL;
	}
	_trashCapacity = 10;
	_trash = new AMateria*[_trashCapacity];
	for (size_t i = 0; i < _trashCapacity; i++){
		_trash[i] = NULL;
	}
}

MateriaSource::MateriaSource(const MateriaSource &other) : _trashCapacity(other._trashCapacity){
	for (size_t i = 0; i < 4; i++){
		if (other._materias[i]){
			_materias[i] = other._materias[i]->clone();
		}
		else{
			_materias[i] = NULL;
		}
	}
	_trash = new AMateria*[_trashCapacity];
	for (size_t i = 0; i < _trashCapacity; i++){
		if (other._trash[i]){
			_trash[i] = other._trash[i]->clone(); 
		}
		else{
			_trash[i] = NULL;
		}
	}
	
}

MateriaSource::~MateriaSource(void){
	for (size_t i = 0; i < 4; i++){
		if (_materias[i]){
			delete _materias[i];
			_materias[i] = NULL;
		}
	}
	for (size_t i = 0; i < _trashCapacity; i++){
		if (_trash[i]){
			delete _trash[i];
		}
	}
	delete[] _trash;
}

MateriaSource	&MateriaSource::operator=(const MateriaSource &other){
	if (this == &other){
		return (*this);
	}
	for (size_t i = 0; i < 4; i++){
		if (other._materias[i]){
			if (_materias[i]){
				delete _materias[i];
			}
			_materias[i] = other._materias[i]->clone();
		}
		else{
			if (_materias[i]){
				delete _materias[i];
			}
			_materias[i] = NULL;
		}
	}
	//primero vaciar todo el _trash ya creado
	for (size_t i = 0; i < _trashCapacity; i++){
		if (_trash[i]){
			delete _trash[i];
		}
	}
	delete[] _trash;
	//ahora copiarlo
	_trashCapacity = other._trashCapacity;
	_trash = new AMateria*[_trashCapacity];
	for(size_t i = 0; i < _trashCapacity; i++){
		if (other._trash[i]){
			_trash[i] = other._trash[i]->clone();
		}
		else{
			_trash[i] = NULL;
		}
	}
	return (*this);
}

void		MateriaSource::sendToTrash(AMateria *materia){
	size_t i = 0;
	//ver si esta ya "materia" en el trash
	while (i < _trashCapacity){
		if (materia == _trash[i]){
			return; //salir si esta
		}
		i++;
	}
	//busqueda de hueco en _trash para dejar la materia
	i = 0;
	while (i < _trashCapacity && _trash[i]){
		i++;
	}
	if (i < _trashCapacity){
		_trash[i] = materia;
	}
	else{//reajustar para hacer mas hueco
		AMateria	**aux;
		size_t oldCap = _trashCapacity;
		_trashCapacity += 10;
		aux = new AMateria*[_trashCapacity]; //nueva capacidad aumentada
		
		//copia a aux de _trash y reasignacion
		for (size_t j = 0; j < oldCap; j++){
			aux[j] = _trash[j];
		}
		//lo demas nuevo asignar NULL
		for (size_t j = oldCap; j < _trashCapacity; j++){
			aux[j] = NULL;
		}
		delete[] _trash;
		_trash = aux;

		//encontrar hueco para el valor no almacenado materia
		for (size_t k = 0; k < _trashCapacity; k++) {
        	if (!_trash[k]) {
            	_trash[k] = materia;
        		break;
       		}
		}
	}
}

void		MateriaSource::learnMateria(AMateria *materia){
	size_t i = 0;

	while (i < 4 && _materias[i]){
		i++;
	}
	if (materia && i < 4){
		_materias[i] = materia->clone();
		sendToTrash(materia); //asi no doble delete por que no se puede poner a NULL
	}
	else{
		sendToTrash(materia); //si no hay hueco hay que apartarlo para eliminarlo en el destructor
	}
}
AMateria 	*MateriaSource::createMateria(std::string const &type){
	if (type == "ice"){
		return (new Ice());
	}
	else if (type == "cure"){
		return (new Cure());
	}
	else if (type == "fire"){
		return (new Fire());
	}
	return (0);
}


