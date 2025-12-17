/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:12:40 by jrollon-          #+#    #+#             */
/*   Updated: 2025/12/17 13:31:36 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_H
# define BUREAUCRAT_H

#include <iostream>
#include "AForm.hpp"
#include <cstdlib> //system("clear")

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[38;2;255;0;0m"
# define GREEN "\033[38;2;0;255;0m"
# define YELLOW "\033[38;5;226m"
# define BLUE "\033[38;2;0;100;255m"
# define MAGENTA "\033[38;2;100;50;255m"
# define CYAN "\033[38;2;0;200;255m"
# define WHITE "\033[37m"


/*Recordar: El const primero es para no mofidicar la variable.
el último const para no modificar el objeto
Y cuando el valor de retorno no es por &(referencia) no sirve de nada...
...poner const antes por que es una copia(devuelve por valor) y da igual...
...modificar dicho valor ya que el original estará protegido.*/
class Bureaucrat{
private:
	const std::string	_name;
	int					_grade;

public: //constructores destructores
	Bureaucrat(void);
	Bureaucrat(const std::string &name, const int grade);
	Bureaucrat(const Bureaucrat &origin);
	Bureaucrat &operator=(const Bureaucrat &origin);
	~Bureaucrat(void);

public: //getters
	const std::string	&getName(void) const;
	int					getGrade(void) const; //no hace falta & por que el tipo es muy básico

public: //setter
	int	incrementGrade(void);//sin primer const por que es copia y da igual modificarlo fuera
	int	decrementGrade(void);//sin segundo const por que queremos modificar el objeto en si.
	
public: //excepciones internas
	class GradeTooHighException{ //no clase canónica segun ejercicio
	public:
		GradeTooHighException(const std::string &name); //necesita un constructor para pasarle el nombre del objeto que tiene error
		const std::string	&what() const; //& para evitar copias de lo que devuelve
	private:
		std::string	_msg;
	};

	class GradeTooLowException{
	public:
		GradeTooLowException(const std::string &name);
		const std::string 	&what() const;
	private:
		std::string _msg;
	};
public:
	void	signForm(AForm &form) const;
	void	executeForm(AForm const &form) const;
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &person);

#endif
