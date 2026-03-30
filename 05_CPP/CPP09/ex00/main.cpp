/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:10:40 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/30 18:59:29 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int ac, char** av){
	if (ac != 2){
		std::cerr << "Error: could not open file" << std::endl;
		return (1);
	}
	try{
		BitcoinExchange be("data.csv");
		(void)av;
		std::map<std::string, float>::const_iterator it = be._data.begin();
		for (;it != be._data.end(); it++){
			std::cout << it->first << " " << it->second << std::endl;
		}
			
	}
	catch (const std::exception& ex){
		std::cerr << ex.what() << std::endl;
		return (1);
	}
	
	return (0);
}