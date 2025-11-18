/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:12:33 by jrollon-          #+#    #+#             */
/*   Updated: 2025/11/18 13:40:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

/////////////////////
///// CANONICAL /////
/////////////////////
Bureaucrat::Bureaucrat(void) : _name("Mr Noone"), _grade(150){
	std::cout << GREEN "🧑🏻‍🎓	Default Bureaucrat constructor called." RESET << std::endl;
}

Bureaucrat::Bureaucrat(const std::string &name, const int grade) 
	: _name(name), _grade(grade){
	if(grade < 1)
		throw GradeTooHighException(_name);
	else if (grade > 150)
		throw GradeTooLowException(_name);
	std::cout << GREEN "🤵🏻‍♀️	Bureaucrat constructor called for " RESET
		<< name << "." << std::endl;		
}

Bureaucrat::Bureaucrat(const Bureaucrat &origin)
	: _name(origin._name), _grade(origin._grade){
	std::cout << CYAN "🐑🤵🏻‍♀️	Bureaucrat created from "
		<< origin._name 
		<< "." << std::endl;		
}

//copia no puede inicializarse por lista por lo que el const de name no se puede alterar
Bureaucrat &Bureaucrat::operator=(const Bureaucrat &origin){
	if (this != &origin)
		_grade = origin._grade;
	std::cout << YELLOW "🐑🧑🏼‍⚕️	Bureaucrat copied (=) only in grade (const name)" RESET 
		<< std::endl;
	return (*this);
}

Bureaucrat::~Bureaucrat(void){
	std::cout << "💀​ " << _name << RED " bureaucrat destroyed" RESET << std::endl;
}

///////////////////
///// GETTERS /////
///////////////////
const std::string &Bureaucrat::getName(void) const{
	return (_name);
}	

int	Bureaucrat::getGrade(void) const{
	return (_grade);
}


///////////////////
///// SETTERS /////
///////////////////
/*Notas: el throw se podria haber hecho:
GradeTooHighException ex;
throw ex;
pero al hacer GradeTooHighException() estamos construyendo el objeto temporalmente
y por lo tanto no hace falta declararlo. es como lanzar un int y hacerlo 
throw 32 directamente.*/
int	Bureaucrat::incrementGrade(void){
	_grade--;
	if (_grade < 1)
		throw GradeTooHighException(_name); //leer notas arriba. Necesita un catch fuera
	return (_grade); //si hay throw no hay return
}

int	Bureaucrat::decrementGrade(void){
	_grade++;
	if (_grade > 150)
		throw GradeTooLowException(_name);
	return (_grade);
}

//////////////////////
///// EXCEPTIONS /////
//////////////////////
Bureaucrat::GradeTooHighException::GradeTooHighException(const std::string &name)
	: _msg("The Bureaucrat " + name + " is too HIGH in degree. Max is 1."){}

/*al ser lo que devuelvo una referencia (&) necesito componer el msg
dentro del constructor, por que si no haria un temporal std::string y eso fuera de esta
funcion what, seria una referencia invalida borrada. Si no fuera un const std::string&
entonces sí que podría haberlo compuesto aquí el msg como hago en la asignación de _msg*/
const std::string &Bureaucrat::GradeTooHighException::what() const{
	return (_msg);
}

Bureaucrat::GradeTooLowException::GradeTooLowException(const std::string &name)
	: _msg("The Bureaucrat " + name + " is too LOW in degree. Min is 150."){}

const std::string &Bureaucrat::GradeTooLowException::what() const{
	return (_msg);
}

//////////////////////
///// SIGN FORMS /////
//////////////////////

void noSignOut(const AForm &form, const Bureaucrat &bureaucrat){
	std::cout << "✒️​📜	"
	<< bureaucrat.getName() << YELLOW << " couldn't sign "
	<< form.getName()
	<< " because ";
}

void signOut(const AForm &form, const Bureaucrat &bureaucrat){
	std::cout << "✒️​📜 "
	<< bureaucrat.getName() << GREEN << " signed "
	<< form.getName()
	<< RESET << std::endl;
}

void Bureaucrat::signForm(AForm &form) const{
	if (form.getSigned()){ //Ya está firmado
		noSignOut(form, *this);	
		std::cout << " it is already signed." << RESET << std::endl;
	}
	else{ //no firmado
		if (_grade > form.getSignGrade()){ //Grado insuficiente
			noSignOut(form, *this);
			std::cout << " his grade is not high enough." << RESET << std::endl;
		}
		else{ //grado suficiente
			form.beSigned(*this); //firmamos
			signOut(form, *this);
		}	
	}
}

void Bureaucrat::executeForm(AForm const &form) const{
	try{
		form.execute(*this);
		std::cout << GREEN << _name << " executed " << form.getName() << RESET << std::endl;
	}
	catch (std::exception &e){
		std::cout << RED << _name << " couldn't execute " << form.getName()
			<< " because " << e.what() << RESET << std::endl;
	}
}


///////////////////////
///// << OPERATOR /////
///////////////////////
std::ostream &operator<<(std::ostream &out, const Bureaucrat &person){
	out << CYAN
	<< person.getName()
	<< ", bureaucrat grade " 
	<< person.getGrade() << RESET
	<< "\n"; 
	return (out); //esto es para encadenar varios std::cout << clase1 << clase2 etc..
}
