/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:48:09 by jrollon-          #+#    #+#             */
/*   Updated: 2025/11/24 14:14:52 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "colors.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern(void){
	std::cout << GREEN "Intern class created" RESET << std::endl;
}

Intern::Intern(const Intern &other) {
	(void)other;
	std::cout << YELLOW "Nothing to copy from Intern but applied" RESET << std::endl;
}

Intern &Intern::operator=(const Intern &other){
	(void)other;
	std::cout << YELLOW "Nothing to assign but is applied" RESET << std::endl;
	return *this;
}

Intern::~Intern(void){
	std::cout << RED "Class Intern Destroyed" RESET << std::endl;
}

//FUNCIONES PARA EL MAKEFORM QUE DEVUELVEN UN PUNTERO

AForm *createShrubbery(const std::string &target){
	return new ShrubberyCreationForm(target);
}

AForm *createRobotomy(const std::string &target){
	return new RobotomyRequestForm(target);
}

AForm *createPresidential(const std::string &target){
	return new PresidentialPardonForm(target);
}

//////////////////


AForm *Intern::makeForm(const std::string &name, const std::string &target) const{
	static const std::string forms_type[] = { //poner static mejora el rendimiento. Si no se crea el array cada vez que entra en la función.
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};
	
	static AForm *(*creators[3])(const std::string &); //es un array de funciones para comparar con el name. Static por lo mismo de arriba
	creators[0] = createShrubbery;
	creators[1] = createRobotomy;
	creators[2] = createPresidential;  
	
	for (size_t i = 0; i < 3; i++){
		if (name == forms_type[i]){
			std::cout << GREEN "Intern creates " << name << RESET << std::endl;
			return creators[i](target); //de esta manera llama a la funcion correcta. Maravilloso!! y como es puntero ya la propia funcion lo que se devuelve, pues genial.
		}
	}
	std::cout << RED "Error: Form not found." RESET << std::endl;
	return NULL;
}

