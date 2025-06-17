/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:21:12 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/17 15:03:59 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"
#include "phonebook.hpp"

int	main(void)
{
	PhoneBook	phonebook;
	Contact		contact;
	std::string	command;

	while(1)
	{
		std::cout << "Command (ADD, SEARCH, EXIT): ";
		if(!std::getline(std::cin, command)) //CtrlD protection
			break ;	
		if (command == "ADD")
			enterContact(&phonebook, &contact);
		else if (command == "SEARCH")
			searchContact(&phonebook);
		else if (command == "EXIT")
			break ;	
		else
			std::cout << "Not a valid command: " << std::endl;
		std::cout << "\033[2J\033[H";
	}
	return (0);
}
