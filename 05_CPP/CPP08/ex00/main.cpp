/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:00:29 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/04 15:15:50 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <vector>


int	main(void){
	std::vector<int> c_vector;
	fill_container(c_vector);
	print_container(c_vector);
	
	try{
		easyfind(c_vector, 2);
	}
	catch(const std::exception& e){
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}
