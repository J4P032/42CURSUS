/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:47:24 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/14 21:54:56 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"


// CONSTRUCTORS DESTRUCTORS *******************************


Contact::Contact(void)
{
	//do nothing
}

Contact::~Contact(void)
{
	//do nothing
}

 
 
// SETTERS ***********************************************

void	Contact::setFirstName(std::string name)
{
	if (!name.empty())
		this->_firstName = name;
}

void	Contact::setLastName(std::string surname)
{
	if (!surname.empty())
		this->_lastName = surname;
}

void	Contact::setNickname(std::string nick)
{
	if (!nick.empty())
		this->_nickname = nick;
}

void	Contact::setPhoneNumber(std::string phone)
{
	if (!phone.empty())
		this->_phoneNumber = phone;
}

void	Contact::setDarkestSecret(std::string secret)
{
	if (!secret.empty())
		this->_darkestSecret = secret;
}



// GETTERS *************************************************

std::string	Contact::getFirstName(void) const
{
	return 	this->_firstName;
}

std::string	Contact::getLastName(void) const
{
	return 	this->_lastName;
}

std::string	Contact::getNickname(void) const
{
	return 	this->_nickname;
}

std::string	Contact::getPhoneNumber(void) const
{
	return 	this->_phoneNumber;
}

std::string	Contact::getDarkestSecret(void) const
{
	return 	this->_darkestSecret;
}
