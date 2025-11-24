/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:59:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/11/14 13:01:19 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

class PresidentialPardonForm : public AForm{
private:
	std::string	_target;
	
public:
	PresidentialPardonForm(void);
	PresidentialPardonForm(const std::string &target);
	PresidentialPardonForm(const PresidentialPardonForm &other);
	PresidentialPardonForm &operator=(const PresidentialPardonForm &other);
	~PresidentialPardonForm(void);

public:
	const std::string &getTarget(void) const;

public:
	void execute(Bureaucrat const &executor) const;
};

#endif
