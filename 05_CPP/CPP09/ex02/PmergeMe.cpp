/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:26:08 by jrollon-          #+#    #+#             */
/*   Updated: 2026/04/07 12:43:54 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/* class	PmergeMe{
private:
	std::vector<int>	_vector;
	std::deque<int>		_deque;

public:
	PmergeMe(void);
	PmergeMe(const PmergeMe&);
	PmergeMe& operator=(const PmergeMe&);
	~PmergeMe(void);
	
}; */

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