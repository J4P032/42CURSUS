/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:12:45 by jrollon-          #+#    #+#             */
/*   Updated: 2025/12/16 16:21:18 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <typeinfo>

int	main(void){
	system("clear");
	try{
		Bureaucrat b; //1
		Bureaucrat b140("Manuel", 140); //2
		std::cout << b;
		b = b140;
		std::cout << b;
		Bureaucrat b3(b140); //3
		std::cout << b3;
	
		std::cout << "-----------------" << std::endl;
		
		Form	form; //1
		Form	form140("Nacimiento", 140, 132); //2
		std::cout << form << std::endl;
		std::cout << form140 << std::endl;
		b140.signForm(form140);
		std::cout << form140 << std::endl;
		form = form140;
		std::cout << form << std::endl;
		Form	form_copia(form140); //3
		std::cout << form_copia << std::endl;
		//Form ("patata", 0, 170); //compondra un tipo de mensaje 
		//y estas tres lineas compondran otra excepcion
		Form		form2("Form2", 2, 2);
		Bureaucrat	b4("B4", 4);
		b4.signForm(form2);
		
	}
	catch(Bureaucrat::GradeTooHighException &ex){
		std::cout << RED "⛔ ERROR: " << ex.what() << std::endl;	
	}
	catch(Bureaucrat::GradeTooLowException &ex){
		std::cout << RED "⛔ ERROR: " RESET << ex.what() << std::endl;	
	}
	catch(std::exception &ex){
		if (typeid(ex) == typeid(Form::GradeTooHighException))
			std::cout << RED "⛔ ERROR: " << ex.what() << RESET << std::endl;	
		if (typeid(ex) == typeid(Form::GradeTooLowException))
			std::cout << RED "⛔ ERROR: " << ex.what() << RESET << std::endl;	
	}
	
	catch(...){ //cualquier tipo de excepción lanzada. Siempre tiene que ser la última
		std::cout << RED "⛔ Other type of Error Ocurred" << std::endl;
	}
	std::cout << BLUE "END" RESET << std::endl;
	return (0);
}
