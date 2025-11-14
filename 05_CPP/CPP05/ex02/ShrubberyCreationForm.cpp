/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:59:09 by jrollon-          #+#    #+#             */
/*   Updated: 2025/11/14 12:05:40 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream> //para crear el archivo del execute
#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void) 
	: AForm("nothing", 145, 137), _target("none"){
	std::cout << GREEN "🌱	Default ShrubberyForm constructor called." RESET << std::endl;		
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm("nothing", 145, 137), _target(target){
	std::cout << GREEN "🌱	ShrubberyForm constructor called." RESET << std::endl;		
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
	: AForm(other.getName(), other.getSignGrade(), other.getExecGrade())
		, _target(other.getTarget()){
	copySigned(other.getSigned());
	std::cout << CYAN "🐑🌱	ShrubberyForm created from " RESET << other.getName() << std::endl;
}
		
ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other){
	if (this != &other){
		_target = other._target;
		copySigned(other.getSigned());
		std::cout << YELLOW "🐑🌱	ShrubberyForm copied (=) only Signed and Target as others are constant." RESET << std::endl;
	}
	return *this;	
}

ShrubberyCreationForm::~ShrubberyCreationForm(){
	std::cout << RED "💀🌱	Form " RESET << getName() << RED " destroyed." RESET << std::endl;
}

const std::string &ShrubberyCreationForm::getTarget(void) const{
	return _target;
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const{
	if (!getSigned())
		throw NotSignedException(getName());
	if (executor.getGrade() > getExecGrade())
		throw GradeTooHighException(getName());
	std::ofstream file((_target + "_shrubbery").c_str()); //"file" es solo el nombre de la variable. Puede ser cualquier otro.
	if (!file)
    	throw std::runtime_error("Cannot create the file");
	file << "   🌲\n";
	file << "  🌲🌲\n";
	file << " 🌲🌲🌲\n";
	file << "   ||\n";
	file.close();
}
