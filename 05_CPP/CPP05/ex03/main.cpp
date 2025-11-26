/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:12:45 by jrollon-          #+#    #+#             */
/*   Updated: 2025/11/26 12:58:05 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include <typeinfo> //para typeid valor de la excepción
#include <ctime> //para meter el time de C

void	freeAll(AForm *f1, AForm *f2, AForm *f3){
	if (f1)
		delete f1;
	if (f2)
		delete f2;
	if (f3)
		delete f3;
}


int	main(void){
	system("clear");
	std::srand(std::time(NULL));//inicializa la semilla para el rand() de Robotomy
	
	//las defino fuera del try para que no sean locales al Try y asi poderlas liberar luego.
	Intern	intern;
	AForm *f1 = NULL;
	AForm *f2 = NULL;
	AForm *f3 = NULL;
	
	try{
		Bureaucrat a; //nivel 150
		Bureaucrat b("Manuel", 140); //segundo
		std::cout << a;
		a = b;
		std::cout << a;
		Bureaucrat c(b); //3
		std::cout << c;
		Bureaucrat d("Dios", 1);
		
		/* Ahora no debe ser creados asi los formularios...
		ShrubberyCreationForm f1("form_Shrubbery");
		RobotomyRequestForm f2("form_Robot");
		PresidentialPardonForm f3("form_President");
		sino fuera del try su declaración (para luego ser liberadas), arriba del mismo ya que
		todo lo definido en el try son variables locales */

		f1 = intern.makeForm("shrubbery creation", "Shrubbery form"); //reserva memoria
		f2 = intern.makeForm("robotomy request", "Robotomy form"); //reserva memoria
		//f3 = intern.makeForm("presidential pardon", "Presidential form"); //reserva memoria
		f3 = intern.makeForm("patata", "patata form");//fallara
		
		if (f1) //necesario por que si f1 es NULL tendriamos SEGFAULT
			d.signForm(*f1); //ok
		//d.executeForm(f1); //ok
		Bureaucrat e("Buro_shrubbery", 130);
		if (f1){
			e.executeForm(*f1); //lo hace por que fue firmado por "dios"
			b.executeForm(*f1); //no lo hará no puede pero continua por el catch se recoge en el Bureucrat::executeForm
		}
		Bureaucrat f("Buro_Robo", 45);
		if (f2){
			f.signForm(*f2);
			f.executeForm(*f2);//siempre se ejecutara pero robotomizara un 50% de las veces
		}
		Bureaucrat g("DogySanxe", 5);
		if (f3){
			g.signForm(*f3);
			g.executeForm(*f3);
		}
		//Bureaucrat fallo("fallo", 0); //se saldrá del try
		
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
	freeAll(f1, f2, f3);
	return (0);
}
