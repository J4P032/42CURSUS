/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:33:06 by jrollon-          #+#    #+#             */
/*   Updated: 2025/11/14 12:49:58 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

RobotomyRequestForm::RobotomyRequestForm(void) 
	: AForm("nothing", 72, 45), _target("none"){
	std::cout << GREEN "🤖	Default RobotomyForm constructor called." RESET << std::endl;		
}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
	: AForm("nothing", 72, 45), _target(target){
	std::cout << GREEN "🤖	RobotomyForm constructor called." RESET << std::endl;		
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
	: AForm(other.getName(), other.getSignGrade(), other.getExecGrade())
		, _target(other.getTarget()){
	copySigned(other.getSigned());
	std::cout << CYAN "🐑🤖	RobotomyForm created from " RESET << other.getName() << std::endl;
}
		
RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other){
	if (this != &other){
		_target = other._target;
		copySigned(other.getSigned());
		std::cout << YELLOW "🐑🤖	RobotomyForm copied (=) only Signed and Target as others are constant." RESET << std::endl;
	}
	return *this;	
}

RobotomyRequestForm::~RobotomyRequestForm(){
	std::cout << RED "💀🤖	Form " RESET << getName() << RED " destroyed." RESET << std::endl;
}

const std::string &RobotomyRequestForm::getTarget(void) const{
	return _target;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const{
	if (!getSigned())
		throw NotSignedException(getName());
	if (executor.getGrade() > getExecGrade())
		throw GradeTooHighException(getName());
	//hacer cosas
}
