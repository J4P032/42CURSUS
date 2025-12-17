/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:48:14 by jrollon-          #+#    #+#             */
/*   Updated: 2025/12/17 13:34:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[38;2;255;0;0m"
# define GREEN "\033[38;2;0;255;0m"
# define YELLOW "\033[38;5;226m"
# define BLUE "\033[38;2;0;100;255m"
# define MAGENTA "\033[38;2;100;50;255m"
# define CYAN "\033[38;2;0;200;255m"
# define WHITE "\033[37m"

#ifndef INTERN_HPP
# define INTERN_HPP

class Intern{
public:
	Intern(void);
	Intern(const Intern &other);
	Intern &operator=(const Intern &other);
	~Intern(void);
	
	AForm *makeForm(const std::string &name, const std::string &target) const;
};

#endif

