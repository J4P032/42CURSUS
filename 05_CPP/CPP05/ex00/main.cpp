/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:12:45 by jrollon-          #+#    #+#             */
/*   Updated: 2025/12/17 14:26:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main(void){
	system("clear");
	try{
		Bureaucrat b1; //1
		Bureaucrat b140("Manuel", 140); //2
		std::cout << b1;
		b1 = b140;
		std::cout << b1;
		Bureaucrat b3(b140); //3
		std::cout << b3;
		for (size_t i = 0; i < 150; i++){
			b3.decrementGrade();
			std::cout << b3;
		}
		//Bureaucrat b0("Manolo", 0);
	}

	catch(std::exception &ex){
		if (typeid(ex) == typeid(Bureaucrat::GradeTooHighException)
			|| typeid(ex) == typeid(Bureaucrat::GradeTooLowException))
			std::cout << RED "⛔ ERROR: " << ex.what() << std::endl;
		else
			std::cout << RED "⛔ Other type of Error Ocurred" << RESET << std::endl;	
	}
	std::cout << BLUE "END" RESET << std::endl;
	return (0);
}
