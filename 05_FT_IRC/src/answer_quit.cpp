/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer_quit.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:09:52 by jrollon-          #+#    #+#             */
/*   Updated: 2026/02/16 20:16:53 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommand.hpp"
#include "IRCServ.hpp"
#include <sstream>
#include <iostream>

typedef std::map<int, IRCClient>::iterator SENDER;
typedef	std::pair<std::string, std::string> PAIR_STRING;
typedef std::map<const std::string, int>::const_iterator NICK; 

//need pair because I will reuse the reason the user gives (the parameters msg)
//into the ERROR that sends the server to the sender of QUIT so must separate prefix from msg.
PAIR_STRING	compose_reply(const IRCMessage& msg, const SENDER it_sender){
	std::ostringstream prefix;
	std::ostringstream message;
	PAIR_STRING prefix_msg;

	vectorIteratorPairType it_msg = msg.getParameters();
	
	//compose prefix
	std::string	sender_nick = it_sender->second.getNick();
	if (sender_nick == "")
		sender_nick = "*";
	string			sender_user = it_sender->second.getUsername();
	string			sender_host	= it_sender->second.getHost();
	prefix << ":" << sender_nick << "!" << sender_user << "@" << sender_host << " QUIT :";
	
	//compose menssage, with msg received(parameters)
	if (it_msg.first != it_msg.second){ 
		for (; it_msg.first != it_msg.second; ++it_msg.first){
			message << *it_msg.first;
			if ((it_msg.first + 1) != it_msg.second)
				message << " ";
		}
	}
	//without msg (no parameters)
	else
		message << sender_nick << " is leaving";
	
	prefix_msg.first = prefix.str();
	prefix_msg.second = message.str();
	return (prefix_msg);
}

void send_reply_to_users(const PAIR_STRING& pre_msg, const std::string& nick, int fd, IRCServ& server) {
    std::set<int> fd_sent;
    const std::map<int, IRCClient>& clients = server.getClients();
    std::map<int, IRCClient>::const_iterator it_clients = clients.find(fd);

    if (it_clients == clients.end())
        return;

    // La unión de los dos strings que construiste en compose_reply
    std::string target_msg = pre_msg.first + pre_msg.second + "\r\n";

    pairIterators it_chan = it_clients->second.getChannelIterators();
    const std::map<const string, IRCChannel>& channels = server.getChannels();
    const std::map<const std::string, int>& nicks = server.getNicks();

    while (it_chan.first != it_chan.second) {
        std::string channel_name = *it_chan.first;
        std::map<string, IRCChannel>::const_iterator it_found_chan = channels.find(channel_name);

        if (it_found_chan != channels.end()) {
            PairUserMapIterators it_chann_users = it_found_chan->second.getUsersIterators();
            for (; it_chann_users.first != it_chann_users.second; ++it_chann_users.first) {
                const std::string& t_nick = it_chann_users.first->first;
				std::map<const std::string, int>::const_iterator it_n = nicks.find(t_nick);
				
				if (it_n != nicks.end()) {
					int t_fd = it_n->second;
					// Filtramos al emisor usando 'nick' (para el compilador) y el set de enviados
					if (t_nick != nick && fd_sent.find(t_fd) == fd_sent.end()) {
						server.queue_and_send(t_fd, target_msg);
						fd_sent.insert(t_fd);
					}
				}
			}
		}
		it_chan.first++;
	}
}

void IRCServ::answer_quit(IRCMessage & msg, int fd) {
    SENDER it_sender = clients.find(fd);
    if (it_sender == clients.end())
        return;

    std::string sender_nick = it_sender->second.getNick();
    // prefix_message.first suele ser el prefijo ":nick!user@host"
    // prefix_message.second suele ser el motivo del QUIT
    PAIR_STRING prefix_message = compose_reply(msg, it_sender);

    // Notificar a todos los usuarios que comparten canales con el emisor
    send_reply_to_users(prefix_message, sender_nick, fd, *this);

    // Enviar el mensaje de confirmación de cierre al propio emisor
    std::ostringstream reply_sender;
    reply_sender << "ERROR :Closing Link: " << it_sender->second.getHost() 
                 << " Quit (" << prefix_message.second << ")\r\n";
    queue_and_send(fd, reply_sender.str());

    // Marcar al cliente para ser eliminado físicamente en el bucle principal
    set_clientsToBeRemoved(fd);
}

