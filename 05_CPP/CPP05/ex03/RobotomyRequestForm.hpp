/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:32:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/11/14 12:41:54 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

class RobotomyRequestForm : public AForm{
private:
	std::string	_target;
	
public:
	RobotomyRequestForm(void);
	RobotomyRequestForm(const std::string &target);
	RobotomyRequestForm(const RobotomyRequestForm &other);
	RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
	~RobotomyRequestForm(void);

public:
	const std::string &getTarget(void) const;

public:
	void execute(Bureaucrat const &executor) const;
};

#endif
