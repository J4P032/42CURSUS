/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook_add.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:53:29 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/17 12:47:07 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"
#include "phonebook.hpp"

bool isAsciiOrLatin(const std::string& str)
{
	size_t i = 0;
	while (i < str.size())
	{
		unsigned char c = str[i];
		if ((c & 0x80) == 0x00) // 1-byte ASCII
			i++;
		else if ((c & 0xE0) == 0xC0) // 2-byte char
			i += 2;
		else
			return false; // 3 bytes or more → reject
	}
	return true;
}

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

bool	isAllSpaces(const std::string &str)
{
	size_t	i = 0;
	
	if (str.length() == 0)
		return (false);
	while (i < str.length())
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (false);
		i++;
	}
	return (true);
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
		
		if(!std::getline(std::cin, input))
			break ;
		if (!isAsciiOrLatin(input))
			std::cout << "Error. Please input valid ascii or latin chars" << std::endl;
		else if (phone && !isAlphaNum(input))
			std::cout << "Error. Please input valid phone format" << std::endl;
		else if (isAllSpaces(input))
			std::cout << "Error. Even is a valid input, please not put all spaces or tabs" << std::endl;
		first_time = false;
	}	while (input.empty() || (phone && !isAlphaNum(input)) || !isAsciiOrLatin(input) || isAllSpaces(input));
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
