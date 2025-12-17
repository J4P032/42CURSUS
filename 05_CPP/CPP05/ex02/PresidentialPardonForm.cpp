/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:59:50 by jrollon-          #+#    #+#             */
/*   Updated: 2025/12/17 11:41:10 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

PresidentialPardonForm::PresidentialPardonForm(void) 
	: AForm("nothing", 25, 5), _target("none"){
	std::cout << GREEN "🏛️	Default PresidentialForm constructor called." RESET << std::endl;		
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
	: AForm(target, 25, 5), _target(target){
	std::cout << GREEN "🏛️	PresidentialForm constructor called." RESET << std::endl;		
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other)
	: AForm(other.getName(), other.getSignGrade(), other.getExecGrade())
		, _target(other.getTarget()){
	copySigned(other.getSigned());
	std::cout << CYAN "🐑🏛️	PresidentialForm created from " RESET << other.getName() << std::endl;
}
		
PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other){
	if (this != &other){
		_target = other._target;
		copySigned(other.getSigned());
		std::cout << YELLOW "🐑🏛️	PresidentialForm copied (=) only Signed and Target as others are constant." RESET << std::endl;
	}
	return *this;	
}

PresidentialPardonForm::~PresidentialPardonForm(){
	std::cout << RED "💀🏛️	Form " RESET << getName() << RED " destroyed." RESET << std::endl;
}

const std::string &PresidentialPardonForm::getTarget(void) const{
	return _target;
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const{
	if (!getSigned())
		throw NotSignedException(getName());
	if (executor.getGrade() > getExecGrade())
		throw GradeTooHighException(" lower rank necesary to do it.");
	std::cout << CYAN << _target << " has been pardoned by Zaphod Beeblebrox." RESET << std::endl; 
}
