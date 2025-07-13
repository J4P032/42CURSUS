/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:03:29 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/13 16:50:05 by jrollon-         ###   ########.fr       */
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
}

MateriaSource::MateriaSource(const MateriaSource &other){
	for (size_t i = 0; i < 4; i++){
		if (other._materias[i]){
			_materias[i] = other._materias[i]->clone();
		}
		else{
			_materias[i] = NULL;
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
	return (*this);
}

void		MateriaSource::learnMateria(AMateria *materia){
	size_t i = 0;

	while (i < 4 && _materias[i]){
		i++;
	}
	if (materia && i < 4){
		_materias[i] = materia->clone();
		delete materia; //Se ha de eliminar por que se clona y si no hay Leak
		//materia = NULL; no sirve de nada por qeu materia es simple puntero y deberia ser **
	}
	else{
		delete materia; //si no hay hueco ha de eliminarse. Si no Leak
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


