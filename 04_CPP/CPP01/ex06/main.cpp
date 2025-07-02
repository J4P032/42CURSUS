/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:16:11 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/02 20:48:04 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main(int argc, char **argv){

	if (argc != 2){
		std::cout << "Please: ./harlFilter \"DEBUG_LEVEL\"";
		return (1);
	}
	
	Harl		test;
	std::string	filter[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	size_t		i = 0;

	while (i < 4){
		if (std::string(argv[1]) == filter[i]){
			break ;
		}
		i++;
	}
	
	/*Mejor hubiera sido poner un: for(size_t j=i; j<4; j++){*/
	/*test.complain(filter[j])} pero piden hacerlo con switch*/
	switch (i){
		case 0:
			test.complain(filter[0]);
			test.complain(filter[1]);
			test.complain(filter[2]);
			test.complain(filter[3]);
			break;
		case 1:
			test.complain(filter[1]);
			test.complain(filter[2]);
			test.complain(filter[3]);
			break;
		case 2:
			test.complain(filter[2]);
			test.complain(filter[3]);
			break;
		case 3:
			test.complain(filter[3]);
			break;
		default:
			std::cout << "[ Probably complaining about insignificant problem ]";
			std::cout << std::endl;
			break;
	}
	
	
	
}
