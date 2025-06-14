/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:46:42 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/14 21:18:06 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"

// CONSTRUCTORS DESTRUCTORS *******************************

PhoneBook::PhoneBook(void)
{
	//Do Nothing
}

PhoneBook::~PhoneBook(void)
{
	//Do Nothing
}



// SETTERS ***********************************************

void	PhoneBook::setContacts(int numContact, const Contact &contact)
{
	this->_contacts[numContact % 8] = contact;
}


// GETTERS *************************************************

Contact PhoneBook::getContact(int index) const
{
	return 	this->_contacts[index];
}
