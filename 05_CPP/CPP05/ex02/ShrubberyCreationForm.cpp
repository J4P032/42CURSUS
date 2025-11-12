/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:59:09 by jrollon-          #+#    #+#             */
/*   Updated: 2025/11/11 13:22:45 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void) 
	: AForm("nothing", 145, 137), _target("none"){}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm("nothing", 145, 137), _target(target){}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
	: AForm(other.getName(), other.getSignGrade(), other.getExecGrade())
		, _target(other.getTarget()){}
		
ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other){
	if (this != &other)
	{
		_target = other._target;
		*this = other;
		
	}
	
}


/* class ShrubberyCreationForm : public AForm{
private:
	std::string	_target;
	
public:
	ShrubberyCreationForm(void);
	ShrubberyCreationForm(const std::string &target);
	ShrubberyCreationForm(const ShrubberyCreationForm &other);
	ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);
	~ShrubberyCreationForm(void);

public:
	const std::string &getTarget(void) const;
	
public:
	void execute(Bureaucrat const &executor) const;
}; */


