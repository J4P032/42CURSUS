/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:58:26 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/12 15:34:49 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <algorithm>
#include <numeric> //std::adjacent_difference

Span::Span(void) : _maxSize(0){}

Span::Span(unsigned int	n) : _maxSize(n){
	try{
		/*se usa reserve en vez de resize por que reserva la memoria pero mantiene el
		tamaño del vector en 0 para poder hacer push_back luego.
		intentamos reservar memoria. maxUnsigLong es mucho 16gb*/
		_span.reserve(n); 
	}
	catch (const std::bad_alloc& ex){
		throw std::runtime_error("Not enough memory to create Span of this size");
	}
}

Span::Span(const Span& other) : _span(other._span), _maxSize(other._maxSize){}

Span& Span::operator=(const Span& other){
	_span = other._span;
	_maxSize = other._maxSize;
	return (*this);	
}

Span::~Span(void){}

//ADD NUMBERS PLUS +
void	Span::addNumber(int n){
	if (_span.size() == _maxSize)
		throw std::runtime_error("Max size reached");
	_span.push_back(n);
}

void 	Span::addNumber(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end){
	size_t	size = std::distance(begin, end);
	if (_span.size() + size > _maxSize)
		throw std::runtime_error ("Span don't have enough capacity");
	_span.insert(_span.end(), begin, end);
	
}

Span	Span::operator+(const Span& other) const{
	//ha de ser casteado uno solo por que si casteo cast<unsigned long>(_maxSize + other._maxSize)
	// hará primero la suma siendo overflow y pasado a numero menor y no saltará
	unsigned long totalSize = static_cast<unsigned long>(_maxSize) + other._maxSize; 
	if (totalSize > 4294967295UL)
		throw std::runtime_error("Combined Span size exceeds unsigned int limit");
		
	Span	aux(static_cast<unsigned int>(totalSize)); //ya es seguro
	aux.addNumber(_span.begin(), _span.end());
	aux.addNumber(other._span.begin(), other._span.end());
	return (aux);
}

unsigned long	Span::shortestSpan(void) const{
	if (_span.size() < 2)
		throw std::runtime_error("not enough numbers to calculate shortestSpan");
	
	std::vector<int>	aux = _span;
	std::sort(aux.begin(), aux.end());
	
	std::vector<int>::const_iterator it = aux.begin();
	unsigned long distance = static_cast<long>(*(it + 1)) - static_cast<long>((*it));
	unsigned long minorDist = distance;
	while ((it + 1) != aux.end()){
		distance = static_cast<long>(*(it + 1)) - static_cast<long>(*it);
		if (distance < minorDist)
			minorDist = distance;
		++it;
	}
	return (minorDist);
}


/*Este otro sería FULL STL pero no lo dejo por un problema que restringe 42.
long funcionaría en 64 bits pero NO en 32bits y habría overflow. La solución 
sería hacer aux como long long en vez de solo long. Pero long long no es aceptado
en C++98 así que este código funcionaría en 64bits pero no en 32. El de arriba sí
que funciona en 64 y 32
unsigned long	Span::shortestSpan(void) const{
	if (_span.size() < 2)
		throw std::runtime_error("not enough numbers to calculate shortestSpan");
	
	//Hacemos una copia en un vector de 'long' (64 bits) antes de ordenar. 
   	//Es crucial que sea 'long' porque la diferencia entre el valor máximo (INT_MAX) 
   	//y el mínimo (INT_MIN) es de 4.294.967.295. 
   	//Si restamos dos 'int', el resultado desbordaría (Overflow), convirtiéndose 
   	//en un número negativo (ej. -1). Al devolver ese negativo como 'unsigned long', 
   	//se produciría un Underflow masivo, resultando en un valor erróneo de 18 quintillones.
	std::vector<long>	aux(_span.begin(), _span.end());
	std::sort(aux.begin(), aux.end());
	
	//creamos un vector para guardar las diferencias. Hay que tener cuidado por que
	//adjacent_difference guarda como primer elemento el primer elemento de aux asi:
	//diffs[0] = aux[0];
	//diffs[1] = aux[1] - aux[0];
	//etc.. o sea que luego hay que quitar el primer elemento
	std::vector<long> diffs(aux.size()); //podria ajustarse el size pero es muy poco de memoria extra
	std::adjacent_difference(aux.begin(), aux.end(), diffs.begin());

	return(*std::min_element(diffs.begin() + 1, diffs.end())); //quitamos el primero.
}*/
	
unsigned long	Span::longestSpan(void) const{
	if (_span.size() < 2)
		throw std::runtime_error("not enough numbers to calculate longestSpan");
	long min = static_cast<long>(*std::min_element(_span.begin(), _span.end()));
	long max = static_cast<long>(*std::max_element(_span.begin(), _span.end()));

	return static_cast<unsigned long>(max - min);
}

const std::vector<int>& Span::getVector() const{
	return (_span);
}

std::ostream& operator<<(std::ostream& out, const Span& other){
	std::vector<int> aux = other.getVector();
	std::vector<int>::const_iterator it = aux.begin();
	while (it != aux.end()){
		if (it == aux.begin())
			out << "[";
		out << *it;
		if (it + 1 != aux.end())
			out << ", ";
		else
			out << "]";
		++it;
	}
	return (out);  
}
