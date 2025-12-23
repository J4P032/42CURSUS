/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:51:47 by jrollon-          #+#    #+#             */
/*   Updated: 2025/12/23 13:08:08 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int	main(int argc, char **argv){
	if (argc != 2){
		std::cout << "Usage: ./convert parameter. Parameter must be an string\n";
		return(1);
	}
	ScalarConverter::convert(std::string(argv[1])); //porque recibe un std::string
}

