/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook_add.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:53:29 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/15 18:12:58 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"
#include "phonebook.hpp"

bool	isAlphaNum(const std::string &str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!std::isalnum(str[i]))
		{
			if (str[i] == '+' || str[i] == '-' || str[i] == '(' || str[i] == ')' 
				|| str[i] == ' ' || str[i] == '*' || str[i] == '#')
				;
			else
				return false;
		}
	}
	return true;
}

std::string	askInput(std::string str, bool	phone)
{
	bool		first_time = true;
	std::string	input;
		
	do	{
		std::cout << str;
		if (input.empty() && !first_time)
		{
			std::cout << std::endl;
			std::cout << "Error. You have to input something. Try again." << std::endl;
			std::cout << str;
		}
		std::getline(std::cin, input);
		if (phone && !isAlphaNum(input))
			std::cout << "Error. Please input valid phone format" << std::endl;
		first_time = false;
		//std::cout << "\033[2J\033[H";
	}	while (input.empty() || (phone && !isAlphaNum(input)) );
	return (input);
}

void	enterContact(PhoneBook *phonebook, Contact *contact)
{
	static size_t	num_contacts = 0;
	
	std::cout << "\033[2J\033[H";
	contact->setFirstName(askInput("First name: ", false));
	contact->setLastName(askInput("Last name: ", false));
	contact->setNickname(askInput("Nickname: ", false));
	contact->setPhoneNumber(askInput("Phone: ", true));
	contact->setDarkestSecret(askInput("Darkest secret: ", false));
	phonebook->setContacts(num_contacts, *contact);
	num_contacts++;
}
