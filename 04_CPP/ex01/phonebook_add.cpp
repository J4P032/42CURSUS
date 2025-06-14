/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook_add.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:53:29 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/14 21:53:52 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"
#include "phonebook.hpp"

std::string	askInput(std::string str)
{
	std::string	input;
	do	{
		std::cout << str;
		std::getline(std::cin, input);
		std::cout << "\033[2J\033[H";
	}	while (input.empty());
	return (input);
}


void	enterContact(PhoneBook *phonebook, Contact *contact)
{
	static size_t	num_contacts = 0;
	
	contact->setFirstName(askInput("First name: "));
	contact->setLastName(askInput("Last name: "));
	contact->setNickname(askInput("Nickname: "));
	contact->setPhoneNumber(askInput("Phone: "));
	contact->setDarkestSecret(askInput("Darkest secret: "));
	phonebook->setContacts(num_contacts, *contact);
}
