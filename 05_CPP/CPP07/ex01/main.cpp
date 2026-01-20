/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:26:56 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/20 14:44:47 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

template <typename T, typename F> void iter(T *array, const size_t len, F f){
	for (size_t i = 0; i < len; i++)
		f(array[i]);		
}

template <typename T>
void printValues(T& element){
	std::cout << GREEN << element << RESET << ", " << std::endl;
}

template <typename T>
void printValues(const T& element){
	std::cout << GREEN << element << RESET << ", " << std::endl;
}

int	main (void){

	float		num1 = 32.1f, num2 = 0.4f;
	int			intMatrix[] = {3, 423, 2, -34, 0}; //cuidado!! sin = es C++11
	std::string	frases[] 	= {"hola mundo", "como estas ?", "yo bien", ""};
	double		vacio[] 	= {};
	float* 		pFloats[] 	= {&num1, &num2};
	
	size_t	len = sizeof(intMatrix) / sizeof(intMatrix[0]);
	size_t	len2 = sizeof(frases) / sizeof(frases[0]);
	size_t	len3 = sizeof(vacio) / sizeof(vacio[0]);
	size_t	len4 = sizeof(pFloats) / sizeof(pFloats[0]);	

	iter(intMatrix, len, static_cast<void(*)(int&)>(printValues<int>)); //hay que castear, pq si no no sabe cual pillar de las funciones. Se resolveria con un lamda pero es cpp11
	std::cout << std::endl;
	iter(intMatrix, len, static_cast<void(*)(const int&)>(printValues<int>));
	
	std::cout << YELLOW << "-------Con Strings---------" << RESET << std::endl;

	iter(frases, len2, static_cast<void(*)(std::string&)>(printValues<std::string>));
	std::cout << std::endl;
	iter(frases, len2, static_cast<void(*)(const std::string&)>(printValues<std::string>));
	
	std::cout << YELLOW << "-------Con Doubles Vacios---------" << RESET << std::endl;

	iter(vacio, len3, static_cast<void(*)(double&)>(printValues<double>));
	std::cout << std::endl;
	iter(vacio, len3, static_cast<void(*)(const double&)>(printValues<double>));

	std::cout << YELLOW << "-------Con punteros a float---------" << RESET << std::endl;

	iter(pFloats, len4, static_cast<void(*)(float*&)>(printValues<float*>));
	iter(pFloats, len4, static_cast<void(*)(float* const&)>(printValues<float*>));
	
	

	
	return (0);
}
