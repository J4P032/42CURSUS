/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:26:08 by jrollon-          #+#    #+#             */
/*   Updated: 2026/04/07 19:20:47 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h>
#include <cmath>
#include <algorithm>

int	jacobsthal(int index){
	return ((std::pow(2, index) - std::pow(-1, index)) / 3);
}

PmergeMe::PmergeMe(void){}

PmergeMe::PmergeMe(const PmergeMe& other) : _vector(other._vector), _deque(other._deque) {}

PmergeMe&	PmergeMe::operator=(const PmergeMe& other){
	if (this != &other){
		_vector = other._vector;
		_deque = other._deque;	
	}
	return (*this);
}

PmergeMe::~PmergeMe(void){}

void	PmergeMe::setPmergeMe(int num){
	_vector.push_back(num);
	_deque.push_back(num);
}

//debemos devolver y pasar copias por que es RECURSIVO y asi se conservan los contenedores como deben ser.
std::vector<int>	PmergeMe::fJSort(std::vector<int> c){
	std::vector<std::pair<int, int> >	pairs;
	std::vector<int>					final;
	std::vector<int>					sorted_seconds;
	int									rest;
	
	//para cortar la recursividad infinita
	if (c.size() <= 1)
		return c;
	
	//hacer parejas y poner el numero mayor primero.
	std::vector<int>::const_iterator cit = c.begin();
	while (cit != c.end() && (cit + 1) != c.end()){
		if (*cit >= *(cit + 1))
			pairs.push_back(std::make_pair(*cit, *(cit + 1)));
		else
			pairs.push_back(std::make_pair(*(cit + 1), *cit));
		cit += 2;
	}

	//si son impares almacenar el ultimo numero si no -1 para no considerarlo
	if (c.size() % 2) 
		rest = *cit;
	else
		rest = -1;

	//metemos los pares primeros en otro contenedor ya ordenándolo.
	std::vector<int>	winners;
	for (size_t i = 0; i < pairs.size(); i++)
		winners.push_back(pairs[i].first);
		
	final = fJSort(winners);

	//componer vector de segundos ordenado
	std::vector<bool> used(pairs.size(), false); //para numeros repetidos
	for (size_t j = 0; j < final.size(); j++) {
		for (size_t i = 0; i < pairs.size(); i++) {
			if (!used[i] && pairs[i].first == final[j]) {
				sorted_seconds.push_back(pairs[i].second);
				used[i] = true;
				break;
        	}
    	}
	}

	
	/*insertamos los segundos de pairs pero  siguiendo el indice de la serie Jacobsthal
	0,1,1,3,5,11,21,43,85... por que parece que es mejor rendimiento.
	
	imaginemos que nuestro final = [10, 20, 30, 40]
	hemos ordenado los segundos y por lo tanto queremos meter por jemplo un sorted_seconds[i] = 25
	el std::upper_bound, buscará en final, el numero inmediatamente mayor a 25, que es 30
	el insert lo desplazará a la derecha dicho 30 quedando [10, 20, 25, 30, 40] y así con todos
	los restantes numeros sorted_seconds[i--]*/
	
	int	jacob = 1; //el primero (index = jacob - 1) 
	int	next_jacob_index = 3; //indice del siguiente. el segundo '1' era el 2 (index = 2) (0,1,1,3...)
	int	index_done = -1;
	int	sorted_seconds_size = sorted_seconds.size();
	
	while (index_done < sorted_seconds_size - 1){
		int limit = jacob - 1;
		if (limit >= sorted_seconds_size)
			limit = sorted_seconds_size - 1; //Proteccion segfault
		for (int i = limit; i > index_done; i--){
			//Busca el primer elemento mayor que el que se le pasa(std::upper_bound)
        	std::vector<int>::iterator it = std::upper_bound(final.begin(), final.end(), sorted_seconds[i]);
        	final.insert(it, sorted_seconds[i]); //lo inserta en esa posición y desplaza el resto mayores a la derecha.
		}
		index_done = limit;
		jacob = jacobsthal(next_jacob_index++);
	}
	//nos falta el resto, si existía.
	if (rest != -1){
		std::vector<int>::iterator it = std::upper_bound(final.begin(), final.end(), rest);
    	final.insert(it, rest);
	}
		
	return final;
}


double	PmergeMe::vector_FJ(void){
	double								time;
	struct timeval						start;
	struct timeval						end;
	
	gettimeofday(&start, NULL);
	_vector = fJSort(_vector); //recursividad
	gettimeofday(&end, NULL);
	time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
	
	return time;
}

size_t	PmergeMe::vectorSize(void){
	return (_vector.size());
}


void	PmergeMe::printVector(void) const{
	std::vector<int>::const_iterator it = _vector.begin();
	while (it != _vector.end()){
		std::cout << *it;
		if (it + 1 != _vector.end())
			std::cout << " ";
		it++;
	}
	std::cout << std::endl;
}





	
