/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:37:50 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/12 15:53:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int	main(void){
	Data 		example1;
	uintptr_t	serialNum;
	
	std::cout << GREEN << "Direccion de (Data)example1: ";
	std::cout << RESET << &example1 << std::endl;
	
	serialNum = Serializer::serialize(&example1);
	std::cout << GREEN << "La serializacion es: " << RESET;
	std::cout << serialNum << std::endl;
	
	std::cout << YELLOW << "La deserializacion es: " << RESET;
	std::cout << Serializer::deserialize(serialNum) << std::endl;
	
	std::cout << "--------------------------" << std::endl;

	std::cout << GREEN << "Direccion de NULL: ";
	std::cout << RESET << NULL << std::endl;
	
	serialNum = Serializer::serialize(NULL);
	std::cout << GREEN << "La serializacion es: " << RESET;
	std::cout << serialNum << std::endl;
	
	std::cout << YELLOW << "La deserializacion es: " << RESET;
	std::cout << Serializer::deserialize(serialNum) << std::endl;
	


	
	return (0);
}
