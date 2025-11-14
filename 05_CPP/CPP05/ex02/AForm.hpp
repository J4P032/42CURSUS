/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:20:17 by jrollon-          #+#    #+#             */
/*   Updated: 2025/11/14 12:18:23 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP

# include <iostream>
# include <exception>

class Bureaucrat; //si hago include "Bureaucrat.hpp crea dependencia circular y da error linea 42. esto lo anula"

class AForm{
private:
	const std::string	_fname;
	bool				_signed;
	const int			_sign_grade;
	const int			_exec_grade;

public: //canonica
	AForm(void);
	AForm(const std::string &name, const int sign_grade, const int exec_grade);
	AForm(const AForm &other);
	AForm &operator=(const AForm &other);
	virtual ~AForm(void);

public: //getters
	const std::string	&getName() const;
	bool				getSigned() const;	
	int					getSignGrade() const;
	int					getExecGrade() const;
	
public: //setter
	void	beSigned(const Bureaucrat &bureaucrat); //no const porque modifica _signed
	void	copySigned(bool sign);

public: //excepciones
	class GradeTooHighException : public std::exception{ //al ser heredada de exception podemos capturarla con catch(std::exception)
	public:
		GradeTooHighException(const std::string &name);
		~GradeTooHighException() throw();
		const char	*what() const throw(); //throw() para C++98 en C++11 seria noexcept. La excepción no puede salir de aqui
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

	class NotSignedException : public std::exception{
	public:
		NotSignedException(const std::string &name);
		~NotSignedException() throw();
		const char *what() const throw();
	private:
		std::string _msg;
	};

public:
	virtual void execute(Bureaucrat const &executor) const = 0; //abstracta
	
};

std::ostream &operator<<(std::ostream &out, const AForm &form);

#endif
