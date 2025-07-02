/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:15:34 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/02 20:49:58 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl(void){}
Harl::~Harl(void){}

void	Harl::complain(std::string level)
{
	size_t	i = 0;
	std::string	matrix[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	void (Harl::*functions[])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	
	while (i < 4){
		if (matrix[i] == level){
			break ;
		}
		i++;
	}
	if (i < 4){
		(this->*functions[i])();
	}
}

void	Harl::debug(void){
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "This is a DEBUG msg" << std::endl;
	std::cout << std::endl;
}
void	Harl::info(void){
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "This is a INFO msg" << std::endl;
	std::cout << std::endl;
}
void	Harl::warning(void){
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "This is a WARNING msg" << std::endl;
	std::cout << std::endl;
}
void	Harl::error(void){
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is an ERROR msg" << std::endl;
	std::cout << std::endl;
}
