/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:54:50 by jrollon-          #+#    #+#             */
/*   Updated: 2026/04/01 16:29:55 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int ac, char** av){
	if (ac != 2){
		std::cerr << "Error" << std::endl;
		return 1;
	}
	RPN a;
	if (a.process(av[1]))
		std::cout << a.getNums().top() << std::endl;
	else{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	return 0;
}