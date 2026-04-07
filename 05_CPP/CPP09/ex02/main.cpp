/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:31:06 by jrollon-          #+#    #+#             */
/*   Updated: 2026/04/07 18:43:20 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <climits>
#include <cstdlib>
#include <iomanip>

bool	checkDigit(char c){
	if (!isdigit(c)){
		std::cerr << "Error" << std::endl;
		return false;
	}
	return true;
}

bool	insertSeq(int ac, char** av, PmergeMe& obj){
	for (int i = 1; i < ac; i++){
		char* aux = av[i];
		
		if (aux && !aux[0]){
			std::cerr << "Error" << std::endl;
			return false;
		}
		
		for (int j = 0; aux && aux[j]; j++){
			if (!checkDigit(aux[j]))
				return false;
		}

		long number = strtol(av[i], NULL, 10);
		if (number > INT_MAX){
			std::cerr << "Error" << std::endl;
			return false;
		}
		obj.setPmergeMe(number);
	}
	return true;
}

int	main(int ac, char** av){
	if (ac == 1){
		std::cerr << "Error" << std::endl;
		return 1;
	}
	PmergeMe a;
	if (!insertSeq(ac, av, a))
		return 1;
	
	double	time;
	std::cout << "Before:\t";
	a.printVector();
	time = a.vector_FJ();
	std::cout << "After:\t";
	a.printVector();	
	std::cout << "Time to process a range of\t" << a.vectorSize() << " elements with std::vector : ";
	std::cout << std::fixed << std::setprecision(5) << time << " us" << std::endl;
	

	return 0;
}