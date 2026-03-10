/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:58:26 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/10 16:00:10 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <algorithm>

Span::Span(void) : _maxSize(0){}

Span::Span(unsigned int	n) : _maxSize(n){
	if (n == 0)
		return ;
	for (size_t i = 0; i < n; ++i){
		_span.push_back(0);
	}
}

Span::Span(const Span& other) : _maxSize(other._maxSize), _span(other._span){}

Span& Span::operator=(const Span& other){
	_maxSize = other._maxSize;
	_span = other._span;
	return (*this);	
}

Span::~Span(void){}

void	Span::addNumber(int n){
	if (_span.size() == _maxSize)
		throw std::runtime_error("Max size reached");
	_span.push_back(n);
}

int		Span::shortestSpan(void) const{
	int	smallest;
	int	last_biggest;
	int	biggest;
	
	if (_maxSize < 1)
		throw std::runtime_error("not enough numbers to calculate shortestSpan");
	std::vector<int>::const_iterator it = _span.begin();
	smallest = *it;
	biggest = *it;
	last_biggest = biggest;
	while (it != _span.end()){
		if (*it < smallest)
			smallest = *it;
		if (*it > biggest){
			last_biggest = biggest;
			biggest = *it;
		}
		it++;
	}
	
		

}



/* class	Span{
	Span(void);
	Span(unsigned int);
	Span(const Span&);
	Span& operator=(const Span&);
	~Span(void);
	
	void	addNumber(int);
	int		shortestSpan(void) const;
	int		longestSpan(void) const;
}; */
