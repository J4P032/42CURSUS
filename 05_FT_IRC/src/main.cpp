/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:17:48 by user1             #+#    #+#             */
/*   Updated: 2026/02/04 15:33:48 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCServ.hpp"
#include "utils.hpp"
#include <iostream>

// #include "IRCChannel.hpp"
// #include "IRCCommand.hpp"






int main(int ac, char **av)
{
	if (ac != 3) {
		std::cerr << "Usage: ircserver <port> <client_password>" << std::endl;
		return 1;
	}

	std::pair<int, bool> pairPort = ft_atoi(av[1]);
	if (!pairPort.second) {
		std::cerr << "Invalid server port" << std::endl;
		return 1;
	}

	try {
			IRCServ server(pairPort.first, av[2]);
			server.run();
	}
	catch(std::runtime_error &e) {
			std::cerr << e.what() << std::endl; 
			return 1;
	}

	return 0;
}
