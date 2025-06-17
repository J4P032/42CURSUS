/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook_search.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:45:21 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/17 12:20:10 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"
#include "phonebook.hpp"

void	printFieldTittles(void)
{
	std::cout << "\033[48;5;208m"; // Orange background
	std::cout << "\033[30m";       // Black font
	std::cout << std::setw(10) << "Index" << "|" << std::setw(10) << "Name" << "|";
	std::cout << std::setw(10) << "Surname" << "|" << std::setw(10) << "Nickname";
	std::cout << std::endl;
	std::cout << "\033[0m"; // Reset Stile
}

/*ñ is a 2 bytes char so I have to find the continuation bytes "10xxxxxx"
That way we count only the bytes for the char (1byte)*/
static size_t visibleLength(const std::string &str)
{
	size_t			len = 0;
	unsigned char	c;
	
	for (size_t i = 0; i < str.length(); i++)
	{
		c = static_cast<unsigned char>(str[i]);
		if ((c & 0xC0) != 0x80) //0xC0=11000000 detects continue byte for UTF8 (10xxxxxx)
			++len;
	}
	return (len);	
}

static std::string padLeft(const std::string &str, size_t width)
{
	size_t vis = visibleLength(str);
    if (vis >= width)
        return str;
    return std::string(width - vis, ' ') + str;
}

void	printContactsTable(Contact contact, std::string (Contact::*getter)(void) const, bool last)
{
	std::string	str = (contact.*getter)();
	if (!str.empty())
	{
		if (visibleLength(str) > 10)
			str = str.substr(0, 9) + "."; //substr 0->index to start copy; 9->num chars to copy
		std::cout << padLeft(str, 10);
		if (!last)
			std::cout << "|";
	}
}


void	printContactData(Contact contact)
{
	std::string	pause;
	
	std::cout << "First name: " << contact.getFirstName() << std::endl;
	std::cout << "Last name: " << contact.getLastName() << std::endl;
	std::cout << "Nickname: " << contact.getNickname() << std::endl;
	std::cout << "Phone number: " << contact.getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << contact.getDarkestSecret() << std::endl;
	std::cout << "Press enter to exit";
	if (!std::getline(std::cin, pause))
		return ;
}

	

void	showContactData(size_t num_contacts, PhoneBook *phonebook)
{
	int	index;
	std::string	input;
	std::string	pause;
	
	if (num_contacts == 0)
	{
		std::cout << "Press enter to exit";
		if (!std::getline(std::cin, pause))
			return ;
		return ;
	}
	do	{
		std::cout << "Contact index: ";
		if (!std::getline(std::cin, input))
			return ;
		index = std::atol(input.c_str());
		if (index > static_cast<int>(num_contacts) || index < 1)
			std::cout << "invalid index, please try again" << std::endl;
	} while (index > static_cast<int>(num_contacts) || index < 1);
	std::cout << "\033[2J\033[H";
	printContactData(phonebook->getContact(index - 1));
}

void	searchContact(PhoneBook *phonebook)
{
	size_t		i = 0;
	size_t		num_contacts = 0;
	std::string	str;

	std::cout << "\033[2J\033[H";
	printFieldTittles();
	while (i < 8)
	{
		if (!phonebook->getContact(i).getFirstName().empty())
		{
			std::cout << std::setw(10) << i + 1 << "|";
			num_contacts++;
		}
		printContactsTable(phonebook->getContact(i), &Contact::getFirstName, false);
		printContactsTable(phonebook->getContact(i), &Contact::getLastName, false);
		printContactsTable(phonebook->getContact(i), &Contact::getNickname, true);
		if (!phonebook->getContact(i).getFirstName().empty())
			std::cout << std::endl;
		i++;
	}
	showContactData(num_contacts, phonebook);
	
}

