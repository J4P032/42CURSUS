/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServ.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:52:51 by user1             #+#    #+#             */
/*   Updated: 2026/02/04 14:46:33 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
#define IRCSERV_HPP


#include <sys/epoll.h>
#include <cstring>
#include <map>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdexcept> 

#include "IRCServ.hpp"
#include "IRCChannel.hpp"
#include "utils.hpp"
#include "IRCClient.hpp"
#include "IRCMessage.hpp"

#define SERVER_NAME "42_irc_server"

class IRCServ {
public:
		IRCServ();
		IRCServ(int listening_port, std::string password);
		~IRCServ();

    int																getListeningSocket() const;
    void															setListeningSocket(int socket);
    void															setClientPassword(std::string& password);
    bool															checkClientPassword(std::string& password) const;
    int																getEpollFd() const;
    void															setEpollFd(int fd);
    const std::map<int, IRCClient>&		getClients() const;
    std::map<int, IRCClient>&					getClients();
    void															setClients(const std::map<int, IRCClient>& newClients);
    struct epoll_event*								getEvents();
    const struct epoll_event*					getEvents() const;
    void															setEvent(int fd, epoll_event event);
		void															addToNicks(const string & n);
		void															rmFromNicks(const string & n);
		bool															nickIsUnique(const string & n);
		int 															getFdFromNick(string s);
		std::string												getServerName(void) const;

		
		void			run();
		void			process_client_buffer(int fd);
		void			close_client(int fd);
		void			accept_new_connection();
		bool			read_from_client(IRCClient & client);
		void			answer_command(IRCMessage & msg, int fd);
		void			queue_and_send(int fd, std::string data);
		void			broadcast(int fd, std::string notify_msg);


		void					answer_pass(IRCMessage & msg, int fd);
		void					answer_nick(IRCMessage & msg, int fd);
		void					answer_user(IRCMessage & msg, int fd);
    void					answer_ping(IRCMessage & msg, int fd);

private:
    int listening_socket;
    std::string clientPassword;
    int epoll_fd;
    std::map<int, IRCClient> clients;
    struct epoll_event events[16];
		std::set<std::string> nicks;
		std::map<string, IRCChannel> channels;
		string server_name;
};
#endif
