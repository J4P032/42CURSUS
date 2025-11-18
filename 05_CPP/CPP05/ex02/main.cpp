/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:12:45 by jrollon-          #+#    #+#             */
/*   Updated: 2025/11/18 14:14:27 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <typeinfo> //para typeid valor de la excepción
#include <ctime> //para meter el time de C


int	main(void){
	system("clear");
	std::srand(std::time(NULL));//inicializa la semilla para el rand() de Robotomy
	try{
		Bureaucrat b; //1
		Bureaucrat b140("Manuel", 140); //2
		std::cout << b;
		b = b140;
		std::cout << b;
		Bureaucrat b3(b140); //3
		std::cout << b3;
	
		std::cout << "-----------------" << std::endl;
		
	}
	catch(Bureaucrat::GradeTooHighException &ex){
		std::cout << RED "⛔ ERROR: " << ex.what() << std::endl;	
	}
	catch(Bureaucrat::GradeTooLowException &ex){
		std::cout << RED "⛔ ERROR: " RESET << ex.what() << std::endl;	
	}
	catch(std::exception &ex){
		if (typeid(ex) == typeid(AForm::GradeTooHighException))
			std::cout << RED "⛔ ERROR: " << ex.what() << RESET << std::endl;	
		if (typeid(ex) == typeid(AForm::GradeTooLowException))
			std::cout << RED "⛔ ERROR: " << ex.what() << RESET << std::endl;	
	}
	
	catch(...){ //cualquier tipo de excepción lanzada. Siempre tiene que ser la última
		std::cout << RED "⛔ Other type of Error Ocurred" << std::endl;
	}
	std::cout << BLUE "END" RESET << std::endl;
	return (0);
}
