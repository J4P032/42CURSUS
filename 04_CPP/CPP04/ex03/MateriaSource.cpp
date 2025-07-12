/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:03:29 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/12 21:22:06 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "AMateria.hpp"

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
	
}
AMateria 	*MateriaSource::createMateria(std::string const &type){
	
}


