/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:38:28 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/13 12:11:27 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <vector>
#include <ctime>
#include <cstdlib>

int main_subject(){
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
	std::cout << *it << std::endl;
	++it;
	}
	std::stack<int> s(mstack);
	return 0;
}

template <typename C>
void	fill_container(C& container, size_t size){
	int	num;
	int	neg;
	
	for (size_t i = 0; i < size; ++i){
		num = std::rand();
		neg = std::rand();
		num = !(neg %= 2) ? num : (num * - 1) - 1;
		
		container.push_back(num);
	}
}

template <typename C>
void	print_container(const C& container){
	typename C::const_iterator it = container.begin();
	for (; it != container.end(); ++it){
		if (it != container.begin())
			std::cout << ",";
		std::cout << *it;
	}
	std::cout << std::endl;
}

int	main_mytests(){
	srand(time(NULL));
	
	//PRUEBA CON VECTOR de INTs
	std::cout << "VECTOR<int> TEST" << std::endl;
	std::vector<int> aux;
	fill_container(aux, 10);
	std::cout << "vector<int> formado:" << std::endl;
	print_container(aux);
	MutantStack<int> a(aux.begin(), aux.end());
	std::cout << "MutantStack<int> formado (lee con iteradores):" << std::endl;
	std::cout << a << std::endl;
	std::cout << "MutantStack<int> reversa (reverse iterators):" << std::endl;
	MutantStack<int>::const_reverse_iterator crit = a.rbegin();
	while (crit != a.rend()){
		if (crit != a.rbegin())
			std::cout << ",";
		std::cout << *crit;
		crit++;
	}
	std::cout << std::endl;
	std::cout << "cambio de valor al segundo elemento (no const iterator)" << std::endl;
	MutantStack<int>::iterator it = a.begin() + 1;
	*it = 32;
	std::cout << a << std::endl;

	//COPY OF MONSTERSTACK
	std::cout << "\nCOPY OF MONSTERSTACK" << std::endl;
	MutantStack<int> b;
	b = a;
	std::cout << "MutantStack<int> b = a" << std::endl;
	std::cout << b << std::endl;
	std::cout << "MutantStack<int> c(b)" << std::endl;
	MutantStack<int> c(b);
	std::cout << c << std::endl;

	//LIST of abcd
	std::cout << "\nMutantStack<char> in a LIST" << std::endl;
	
	
	
	return 0;
}


int main(int c, char** v){
	int r;
	
	if (c != 2){
		std::cout << "usage: mutantStack <1 or 2> 1=main of subject, 2=my tests" << std::endl;
		return 1;
	}
	if (std::string(v[1]) == "1")
		r = main_subject();
	else
		r = main_mytests();
	
	return r;
}
