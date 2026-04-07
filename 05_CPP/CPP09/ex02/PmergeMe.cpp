/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:26:08 by jrollon-          #+#    #+#             */
/*   Updated: 2026/04/07 16:17:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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
	for (size_t i = 0; i < pairs.size(); i++)
		final.push_back(pairs[i].first);
		
	final = fJSort(final);
	cit = final.begin();
	for (; cit != final.end(); cit++){
		for (size_t i = 0; i < pairs.size(); i++){
			if (pairs[i].first == *cit){
				sorted_seconds.push_back(pairs[i].second);
				break;
			}
		}
	}

	
	//El primero de los segundos será menor SEGURO que el menor de los MAYORES.
	final.insert(final.begin(), sorted_seconds[0]);
	//insertamos los segundos de pairs. 

	
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




void	PmergeMe::printMe(void) const{
	std::vector<int>::const_iterator it = _vector.begin();
	std::cout << "Before:\t";
	while (it != _vector.end()){
		std::cout << *it;
		if (it + 1 != _vector.end())
			std::cout << " ";
		it++;
	}
	std::cout << std::endl;
}


	
