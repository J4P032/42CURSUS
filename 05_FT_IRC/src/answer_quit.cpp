/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer_quit.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:09:52 by jrollon-          #+#    #+#             */
/*   Updated: 2026/02/13 11:30:34 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommand.hpp"
#include "IRCServ.hpp"
#include <sstream>

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

void	send_reply_to_users(const PAIR_STRING& pre_msg, const std::string& nick, int fd, IRCServ& server){
	//0. prepare a SET of FDs to not repeat msg sent to same user in other channel shared.
	std::set<int>	fd_sent;
	std::set<int>::iterator it_fd;
	
	//1. have the clientes from server.
	const std::map<int, IRCClient>& clients = server.getClients();
	std::map<int, IRCClient>::const_iterator it_clients = clients.find(fd);
	if (it_clients == clients.end())
		return ;
	
	//2. extract channels where our sender is subscribed
	pairIterators it_chan = it_clients->second.getChannelIterators(); //have the iterators (begin/end) of sender channels subscribed
	
	//3. Look in each channel for nicks subscribed and send the msg to them.
	const std::map<const string, IRCChannel>& channels = server.getChannels();
	const std::map<const std::string, int>& nicks = server.getNicks();
	int 				target_fd;
	std::string	target_nick;
	std::string target_msg;
	
	target_msg = pre_msg.first + pre_msg.second + "\r\n";
	while (it_chan.first != it_chan.second){ //run all the set of channels subscribed
		std::string	channel = *it_chan.first;
		
		//grab the iterators in IRCChannel where SENDER is subscribed
		std::map<string, IRCChannel>::const_iterator it_found_chan = channels.find(channel);
		if (it_found_chan != channels.end()){
			PairUserMapIterators it_chann_users = it_found_chan->second.getUsersIterators(); //OOOOH MAMA MY MIND!!!!
			for (; it_chann_users.first != it_chann_users.second; ++it_chann_users.first){
				NICK it_nick = nicks.find(it_chann_users.first->first);
				if (it_nick != nicks.end()){
					target_nick = it_chann_users.first->first;
					target_fd = it_nick->second;
					it_fd = fd_sent.find(target_fd);
					if (nick != target_nick && it_fd == fd_sent.end()){
						server.queue_and_send(target_fd, target_msg);
						fd_sent.insert(target_fd);
					}
				}
			}
		}
		it_chan.first++;
	}
}

void IRCServ::answer_quit(IRCMessage & msg, int fd) {

	//find the sender of QUIT
	SENDER it_sender = clients.find(fd);
	if (it_sender == clients.end())
		return ;
	std::string	sender_nick = it_sender->second.getNick();	
		
	//compose the reply to users that shares same channels with sender.	
	PAIR_STRING	prefix_message = compose_reply(msg, it_sender); //.second (message) needs the \r\n when broadcast.
	
	//Compose reply to USER that orders QUIT
	std::ostringstream reply_sender;
	reply_sender << "ERROR :Closing Link: " << it_sender->second.getHost() << " Quit(" << prefix_message.second << ")\r\n";
	
	//send QUIT msg to shared channels users.
	send_reply_to_users(prefix_message, sender_nick, fd, *this);
	
	//send ERROR QUIT msg to SENDER
	queue_and_send(fd, reply_sender.str());
	 
	//mark the user to be eliminated from server in the loop.
	set_clientsToBeRemoved(fd);
	/*en el loop deberia ser algo asi como:
		std::set<int>& to_remove = get_clientsToBeRemoved();
		std::set<int>::iterator it_fd = to_remove.begin();
		
		while (it_fd != to_remove.end()){
			int fd = *it_fd;
			std::map<int, IRCClient>::iterator it_client = clients.find(fd);
			
			//CASO 1: el cliente YA NO EXISTE en el mapa
			if (it_client == clients.end()){
				to_remove.erase(it_fd++); //lo quitamos de SET ya que no existe
				continue;
			}
			
			//CASO 2: El cliente EXISTE. Lo podemos cerrar?
			if (it_client->second.getObuffer().empty()){ //si se ha vaciado el buffer...
				close_client(fd); //llamada segura a eliminarle por que existe.
				to_remove.erase(it_fd++); //lo quitamos de SET.
			} else {
				++it_fd; //aun hay datos en el SET, lo
			}
		}		*/
}
