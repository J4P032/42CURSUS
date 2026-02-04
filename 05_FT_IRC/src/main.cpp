/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:17:48 by user1             #+#    #+#             */
/*   Updated: 2026/02/03 16:50:50 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCServ.hpp"
#include "utils.hpp"
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
