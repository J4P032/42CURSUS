/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:18:46 by jrollon-          #+#    #+#             */
/*   Updated: 2025/10/29 17:18:27 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <exception>

class Bureaucrat; //si hago include "Bureaucrat.hpp crea dependencia circular y da error linea 42. esto lo anula"

class Form{
private:
	const std::string	_fname;
	bool				_signed;
	const int			_sign_grade;
	const int			_exec_grade;

public: //canonica
	Form(void);
	Form(const std::string &name, const int sign_grade, const int exec_grade);
	Form(const Form &other);
	Form &operator=(const Form &other);
	~Form(void);

public: //getters
	const std::string	&getName() const;
	bool				getSigned() const;	
	int					getSignGrade() const;
	int					getExecGrade() const;
	
public: //setter
	void	beSigned(const Bureaucrat &bureaucrat); //no const porque modifica _signed

public: //excepciones
	class GradeTooHighException : public std::exception{ //al ser heredada de exception podemos capturarla con catch(std::exception)
	public:
		GradeTooHighException(const std::string &name);
		~GradeTooHighException() throw();
		const char	*what() const throw(); //throw() para C++98 en C++11 seria noexcept
	private:
		std::string	_msg;		
	};

	class GradeTooLowException : public std::exception{
	public:
		GradeTooLowException(const std::string &name);
		~GradeTooLowException() throw();
		const char	*what() const throw();
	private:
		std::string	_msg;		
	};
};

std::ostream &operator<<(std::ostream &out, const Form &form);

#endif
