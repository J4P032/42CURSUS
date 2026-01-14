/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:26:56 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/14 17:47:39 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

template <typename T, typename F> void iter(T *array, const size_t len, F f){
	for (size_t i = 0; i < len; i++)
		f(array[i]);		
}

void	printValues(int *array){
	size_t i = 0;
	
	if (array)
		i = sizeof(array) / sizeof(array[0]);
	else
		return ;
	
	for (size_t j = 0; j < i; j++)
		std::cout << GREEN << array[j] << RESET << ", ";
	std::cout << std::endl; 
}

int	main (void){
	int		intMatrix[] = {3, 423, 2, -34, 0}; //cuidado!! sin = es C++11
	size_t	len = sizeof(intMatrix) / sizeof(intMatrix[0]);
	

	
	iter(&intMatrix, len, &printValues);
	

	return (0);
}
