/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:10:40 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/31 16:20:58 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iomanip> //para chequeo con setprecision en test de ver el csv guardado
#include <fstream> //para abrir el archivo con std::ifstream.

void	check_csv(const BitcoinExchange& obj){
	std::map<std::string, float>	aux = obj.get_data();
	std::map<std::string, float>::const_iterator it = aux.begin();
	for (;it != aux.end(); it++)
		std::cout << it->first << " | " << std::fixed << std::setprecision(2) << it->second << std::endl;

}

int	main(int ac, char** av){
	if (ac != 2){
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
	try{
		//abrirlo antes para si no lo abre no hacer el objeto BitcoinExchange por excepcion lanzada
		std::ifstream	inputFile(av[1]);
		if (!inputFile.is_open()) 
			throw std::runtime_error("Error: could not open input file.");
		BitcoinExchange be("data.csv");
		//check_csv(be); //just to test the csv is correctly saved.
		be.process_data(inputFile);
	}
	catch (const std::exception& ex){
		std::cerr << ex.what() << std::endl;
		return (1);
	}
	
	return (0);
}