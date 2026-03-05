/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:00:29 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/05 15:13:43 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <vector>
#include <list>
#include <deque>


int	main(void){
	std::vector<int>	 	c_vector;
	std::list<int>			c_list;
	std::deque<float>		c_deque;
	std::stack<int>			c_stack;
	std::queue<double>		c_queue;
	
	fill_container(c_vector, 25, false); //false = no decimals
	print_container(c_vector);
	fill_container(c_list, 50, false);
	print_container(c_list);
	fill_container(c_deque, 20, false);
	print_container(c_deque);

	fill_container(c_stack, 35, false);
	print_container(c_stack);
	fill_container(c_queue, 195, true); //true = rellenado con decimales
	print_container(c_queue);
	
	try{
		std::cout << std::endl << "//Search in Vector" << std::endl;
		std::vector<int>::iterator it_v = easyfind(c_vector, 2);
		*it_v = 42; //no protejo con un if (it_v != c_vector.end()) por que me protege la excepción que lo parará
		print_container(c_vector);
		
		std::cout << std::endl << "//Search in List" << std::endl;
		std::list<int>::iterator it_l = easyfind(c_list, 41);
		*it_l = 42;
		print_container(c_list);
				
		std::cout << std::endl << "//Search in Deque" << std::endl;
		std::deque<float>::iterator it_d = easyfind(c_deque, 9);
		*it_d = 42.5;
		print_container(c_deque);
		
		//no puedo alterarlos ya que no tiene iteradores
		std::cout << std::endl << "//Search in Stack" << std::endl;
		easyfind(c_stack, 34);
		
		//no lo encontrará ya que he puesto decimales
		std::cout << std::endl << "//Search in Queue" << std::endl;
		easyfind(c_queue, 194);
		
	}
	catch(const std::exception& e){
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}
