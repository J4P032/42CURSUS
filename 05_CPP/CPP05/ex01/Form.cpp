/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:18:58 by jrollon-          #+#    #+#             */
/*   Updated: 2025/10/29 17:48:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

/////////////////////
///// CANONICAL /////
/////////////////////
Form::Form(void) : _fname("Noname"), _signed(false), _sign_grade(150), _exec_grade(150) {
	std::cout << GREEN "📜	Default Form constructor called." RESET << std::endl;
}

Form::Form(const std::string &name, const int sign_grade, const int exec_grade)
	:  _fname(name), _signed(false), _sign_grade(sign_grade), _exec_grade(exec_grade) {
	if (_sign_grade < 1 || _exec_grade < 1)
		throw GradeTooHighException(_fname);
	else if (_sign_grade > 150 || _exec_grade > 150)
		throw GradeTooLowException(_fname);
	std::cout << GREEN "📜	Form " RESET << _fname << GREEN " constructor called." RESET << std::endl;
}

Form::Form(const Form &other)
	: _fname(other._fname), _signed(other._signed), _sign_grade(other._sign_grade), _exec_grade(other._exec_grade){
	std::cout << CYAN "🐑📜	Form created from " RESET << _fname << std::endl; 
}

Form &Form::operator=(const Form &other){
	if (this != &other)
		_signed = other._signed;
	std::cout << YELLOW "🐑📜	Form copied (=) only signed as others are constant." RESET << std::endl;
	return (*this);
}

Form::~Form(void){
	std::cout << RED "💀📜	Form " RESET << _fname << RED " destroyed." RESET << std::endl;
}


///////////////////
///// GETTERS /////
///////////////////
const std::string	&Form::getName() const{
	return (_fname);
}

bool	Form::getSigned() const{
	return (_signed);
}

int	Form::getSignGrade() const{
	return (_sign_grade);
}

int	Form::getExecGrade() const{
	return (_exec_grade);
}

///////////////////
///// SETTERS /////
///////////////////
void	Form::beSigned(const Bureaucrat &bureaucrat){
	(void)bureaucrat; //no lo necesito por lo que pongo abajo
	_signed = true; //comprobación de si puede en Bureaucrat.cpp signForm(Form &form)
}

//////////////////////
///// EXCEPTIONS /////
//////////////////////
Form::GradeTooHighException::GradeTooHighException(const std::string &name)
	: _msg("The form " + name + " grade is too HIGH. Highest possible is 1.") {
}

Form::GradeTooLowException::GradeTooLowException(const std::string &name)
	: _msg("The form " + name + " grade is too LOW. Lowest possible is 150.") {
}

const char *Form::GradeTooHighException::what() const throw(){
	return (_msg.c_str()); //convierte a char* C++98 ok
}

const char *Form::GradeTooLowException::what() const throw(){
	return (_msg.c_str());
}

Form::GradeTooHighException::~GradeTooHighException() throw(){}

Form::GradeTooLowException::~GradeTooLowException() throw(){}

///////////////////////
///// << OPERATOR /////
///////////////////////
std::ostream &operator<<(std::ostream &out, const Form &form){
	out << CYAN "Form " RESET << form.getName()
	<< CYAN " is ";
	if (form.getSigned())
		out << " signed with Sign grade ";
	else
		out << " unsigned with Sign grade ";
	out << RESET << form.getSignGrade()
	<< CYAN ", and executable grade " RESET
	<< form.getExecGrade() << CYAN "." RESET;
	return (out);
}
