/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:33:28 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/02 20:19:19 by jrollon-         ###   ########.fr       */
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
	else{
		std::cout << "I am not calling any function" << std::endl;
	}
}

void	Harl::debug(void){
	std::cout << "This is a DEBUG msg" << std::endl;
}
void	Harl::info(void){
	std::cout << "This is a INFO msg" << std::endl;
}
void	Harl::warning(void){
	std::cout << "This is a WARNING msg" << std::endl;
}
void	Harl::error(void){
	std::cout << "This is an ERROR msg" << std::endl;
}
