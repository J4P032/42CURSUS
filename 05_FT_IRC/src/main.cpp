/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:17:48 by user1             #+#    #+#             */
/*   Updated: 2026/02/16 12:16:20 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCServ.hpp"
#include "utils.hpp"
#include <iostream>
#include <csignal>

// #include "IRCChannel.hpp"
// #include "IRCCommand.hpp"






int main(int ac, char **av)
{
	std::signal(SIGPIPE, SIG_IGN);
	
	/*esto ignora que se mande a un socket no presente.. en el send de queue_and_send hay que meter:
	ssize_t bytes_sent = send(fd, buffer.c_str(), buffer.size(), 0);
	if (bytes_sent == -1) {
    if (errno == EPIPE) {
        // El cliente cerró la conexión. 
        // No pasa nada, ya lo limpiaremos en el loop principal.
        std::cerr << "Error: EPIPE (el cliente cerró el socket)" << std::endl;
        this->set_clientsToBeRemoved(fd); 
    }
}*/

	
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
