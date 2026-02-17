/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer_auth.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:34:32 by mvassall          #+#    #+#             */
/*   Updated: 2026/02/11 15:54:48 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCChannel.hpp"
#include "IRCClient.hpp"
#include "IRCServ.hpp"
#include <sstream>
#include <iostream>

void IRCServ::answer_pass(IRCMessage & msg, int fd)
{
	std::ostringstream recv_pass;
	vectorIteratorPairType range = msg.getParameters();
	for (vector<string>::const_iterator it = range.first; it != range.second; ++it)
		recv_pass << (it == range.first ? "" : " ") << *it;

	if (recv_pass.str().empty())
	{
		queue_and_send(fd, "461 * PASS :Not enough parameters\r\n");
		close_client(fd);
		return;
	}
	if (recv_pass.str() != clientPassword)
	{
		queue_and_send(fd, "464 * :Password incorrect\r\n");
		close_client(fd);
		return;
	}
	clients[fd].setFlag(PASS_FLAG);
}

void IRCServ::answer_nick(IRCMessage & msg, int fd)
{
	if (msg.getParameters().first == msg.getParameters().second) {
		queue_and_send(fd, ":server 431 :No nickname given\r\n");
		return;
	}

	std::string new_nick = *(msg.getParameters().first);
	std::string old_nick = clients[fd].getNick();

	if (!IRCClient::isValidNick(new_nick)) {
		std::string err = ":server 432 * " + new_nick + " :Erroneous nickname\r\n";
		std::cout << "errrrrrrrrrrouneououousssssssssssssssssssssssssssssss" << std::endl;
		queue_and_send(fd, err);
		return;
	}
	if (!nickIsUnique(new_nick) && nicks[new_nick] != fd) {
		std::string err = ":server 433 * " + new_nick + " :Nickname is already in use\r\n";
		queue_and_send(fd, err);
		return;
	}

	clients[fd].setNick(new_nick);
	addToNicks(new_nick, fd);
	clients[fd].setFlag(NICK_FLAG);

	if (old_nick != "") {
		rmFromNicks(old_nick);
		std::string msg = ":" + old_nick + "!" + clients[fd].getUsername() + "@" + clients[fd].getHost() + " NICK " + new_nick + "\r\n";
		queue_and_send(fd, msg);
		broadcast(fd, msg);
	}
	else if (clients[fd].checkFlag(NICK_FLAG) && clients[fd].checkFlag(USER_FLAG) && clients[fd].checkFlag(PASS_FLAG)) 
		sendWelcome(fd);
}

void IRCServ::answer_user(IRCMessage & msg, int fd)
{
	if (clients[fd].getUsername() != "") {
		std::string nick = clients[fd].getNick().empty() ? "*" : clients[fd].getNick();
		queue_and_send(fd, ":server 462 " + nick + " :Unauthorized command\r\n");
		return;
	}

	if (std::distance(msg.getParameters().first, msg.getParameters().second) < 4) {
		std::string nick = clients[fd].getNick().empty() ? "*" : clients[fd].getNick();
		queue_and_send(fd, ":server 461 " + nick + " USER :Not enough parameters\r\n");
		return;
	}

	std::string user = *(msg.getParameters().first);

	if (!IRCClient::isValidUsername(user)) {
		std::string nick = clients[fd].getNick().empty() ? "*" : clients[fd].getNick();
		queue_and_send(fd, ":server 432 " + nick + " :Erroneous username\r\n");
		return;
	}

	clients[fd].setUsername(user);
	clients[fd].setFlag(USER_FLAG);

	if (clients[fd].checkFlag(NICK_FLAG) && clients[fd].checkFlag(USER_FLAG) && clients[fd].checkFlag(PASS_FLAG)) 
		sendWelcome(fd);
}

void IRCServ::queue_and_send(int fd, std::string data)
{
    clients[fd].addToObuffer(data);

    std::string &buffer = clients[fd].getObuffer();
    
    ssize_t sent = send(fd, buffer.c_str(), buffer.size(), MSG_NOSIGNAL);
    if (sent > 0)
        buffer.erase(0, sent);

    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLET;
    if (!buffer.empty())
      ev.events |= EPOLLOUT;

    epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &ev);
}

void IRCServ::broadcast(int fd, std::string notify_msg)
{
	std::set<int> targets;
	targets.insert(fd);

	if (clients.count(fd) == 0) return;
	IRCClient client = clients[fd];
	pairIterators channelIterators = clients[fd].getChannelIterators();
	for (setOfStringsIterator chNameIt = channelIterators.first;
		chNameIt != channelIterators.second; ++chNameIt) {
		string channelName = *chNameIt;
		if (channels.count(channelName) == 0) continue;
		PairUserMapIterators uIts = channels[channelName].getUsersIterators();
		for (map<string,UserMode>::const_iterator uit=uIts.first;
			uit != uIts.second; ++uit) {
				string nickName = uit->first;
				if (nicks.count(nickName) == 0) continue;
				targets.insert(nicks[nickName]);
		} 
	}
	for (std::set<int>::iterator it = targets.begin();
		it != targets.end(); ++it) {
		queue_and_send(*it, notify_msg);
	}
}

void IRCServ::sendWelcome(int fd)
{
    std::string nick = clients[fd].getNick();
    std::string user = clients[fd].getUsername();
    std::string host = clients[fd].getHost();
    std::string sName = getServerName();

    std::string rpl001 = ":" + sName + " 001 " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + "\r\n";
    queue_and_send(fd, rpl001);

    std::string rpl002 = ":" + sName + " 002 " + nick + " :Your host is " + sName + ", running version 1.0\r\n";
    queue_and_send(fd, rpl002);

    std::string rpl003 = ":" + sName + " 003 " + nick + " :This server was created Wed Feb 11 2026\r\n";
    queue_and_send(fd, rpl003);

    std::string rpl004 = ":" + sName + " 004 " + nick + " " + sName + " 1.0 i ntklo\r\n";
    queue_and_send(fd, rpl004);

		std::string rpl376 = ":" + sName + " 376 " + nick + " :End of /MOTD command.\r\n";
		queue_and_send(fd, rpl376);
}
