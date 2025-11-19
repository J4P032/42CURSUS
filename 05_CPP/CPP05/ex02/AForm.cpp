/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:20:36 by jrollon-          #+#    #+#             */
/*   Updated: 2025/11/19 17:38:22 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"

/////////////////////
///// CANONICAL /////
/////////////////////
AForm::AForm(void) : _fname("Noname"), _signed(false), _sign_grade(150), _exec_grade(150) {
	std::cout << GREEN "📜	Default Form constructor called." RESET << std::endl;
}

AForm::AForm(const std::string &name, const int sign_grade, const int exec_grade)
	:  _fname(name), _signed(false), _sign_grade(sign_grade), _exec_grade(exec_grade) {
	if (_sign_grade < 1 || _exec_grade < 1)
		throw GradeTooHighException(_fname);
	else if (_sign_grade > 150 || _exec_grade > 150)
		throw GradeTooLowException(_fname);
	std::cout << GREEN "📜	Form " RESET << _fname << GREEN " constructor called." RESET << std::endl;
}

AForm::AForm(const AForm &other)
	: _fname(other._fname), _signed(other._signed), _sign_grade(other._sign_grade), _exec_grade(other._exec_grade){
	std::cout << CYAN "🐑📜	Form created from " RESET << _fname << std::endl; 
}

AForm &AForm::operator=(const AForm &other){
	if (this != &other)
		_signed = other._signed;
	std::cout << YELLOW "🐑📜	Form copied (=) only signed as others are constant." RESET << std::endl;
	return (*this);
}

AForm::~AForm(void){
	std::cout << RED "💀📜	Form " RESET << _fname << RED " destroyed." RESET << std::endl;
}


///////////////////
///// GETTERS /////
///////////////////
const std::string	&AForm::getName() const{
	return (_fname);
}

bool	AForm::getSigned() const{
	return (_signed);
}

int	AForm::getSignGrade() const{
	return (_sign_grade);
}

int	AForm::getExecGrade() const{
	return (_exec_grade);
}

///////////////////
///// SETTERS /////
///////////////////
void	AForm::beSigned(const Bureaucrat &bureaucrat){
	(void)bureaucrat; //no lo necesito por lo que pongo abajo
	_signed = true; //comprobación de si puede en Bureaucrat.cpp signForm(Form &form)
}

void	AForm::copySigned(bool sign){ //para copiar en el operador= y constructor copia del hijo.
	_signed = sign;
};

//////////////////////
///// EXCEPTIONS /////
//////////////////////
AForm::GradeTooHighException::GradeTooHighException(const std::string &name)
	: _msg("The form " + name + " grade is too HIGH for him.") {
}

AForm::GradeTooLowException::GradeTooLowException(const std::string &name)
	: _msg("The form " + name + " grade is too LOW for him.") {
}

AForm::NotSignedException::NotSignedException(const std::string &name)
	: _msg("The form " + name + " is NOT signed"){}

const char *AForm::GradeTooHighException::what() const throw(){
	return (_msg.c_str()); //convierte a char* C++98 ok
}

const char *AForm::GradeTooLowException::what() const throw(){
	return (_msg.c_str());
}

const char *AForm::NotSignedException::what() const throw(){
	return (_msg.c_str());
}

AForm::GradeTooHighException::~GradeTooHighException() throw(){}

AForm::GradeTooLowException::~GradeTooLowException() throw(){}

AForm::NotSignedException::~NotSignedException() throw(){}

///////////////////////
///// << OPERATOR /////
///////////////////////
std::ostream &operator<<(std::ostream &out, const AForm &form){
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
