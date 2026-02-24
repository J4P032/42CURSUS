/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:17:48 by user1             #+#    #+#             */
/*   Updated: 2026/02/19 13:59:37 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCClient.hpp"
#include "IRCServ.hpp"
#include "utils.hpp"
#include <iostream>
#include <csignal>

volatile sig_atomic_t g_stop = 0; 
void    handle_sigint(int sig){
    (void)sig;
    g_stop = 1;
}

static void closeAll(IRCServ& ircserver) {

    std::map<int,IRCClient>::iterator it;
    for (it = ircserver.getClients().begin(); 
        it != ircserver.getClients().end(); ++it) {
        close(it->first);
    }
    int epollFD = ircserver.getEpollFd();
    epoll_ctl(epollFD, EPOLL_CTL_DEL, epollFD, NULL);
    close(epollFD);
}

int main(int ac, char** av)
{
	std::signal(SIGPIPE, SIG_IGN); //socket non exist.
    std::signal(SIGINT, handle_sigint); //controlC
    std::signal(SIGQUIT, handle_sigint); //control quit
	
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
        closeAll(server);
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
