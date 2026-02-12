/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer_privmsg.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:20:21 by jrollon-          #+#    #+#             */
/*   Updated: 2026/02/10 17:16:04 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommand.hpp"
#include "IRCServ.hpp"
#include <sstream>

static void	to_user(std::vector<std::string>& msg, int fd, std::string & target, IRCServ& server){
	const std::map<int, IRCClient>&						clients	= server.getClients(); //have all the clients
	const std::map<const std::string, int>&		nicks		= server.getNicks();
	std::ostringstream												reply;
	
	
	//1. search if there is an fd for the Nick passed (target).
	std::map<const std::string, int>::const_iterator it_target = nicks.find(target);
	
	//2. search for the creator of the msg to obtain his nick/user/host for the prefix.
	std::map<int, IRCClient>::const_iterator it_sender = clients.find(fd);
  if (it_sender == clients.end())
    return;    
  const IRCClient &sender = it_sender->second;

	//3. construct the reply msg format: :nick!user@host PRIVMSG target :message.
	if (it_target != nicks.end()) {
    int target_fd = it_target->second;
		
		//the prefix
		reply << ":" << sender.getNick() << "!" << sender.getUsername() << "@" << sender.getHost() << " PRIVMSG " << target << " :";

		//now the msg construction
		std::vector<std::string>::const_iterator it_msg = msg.begin();
		if (it_msg != msg.end())
			it_msg++; //jump over the target to find the real msg
		
		for (;it_msg != msg.end(); ++it_msg){
			reply << *it_msg;
			if (it_msg + 1 != msg.end())
				reply << " "; //add separator between words.
		}
		
		//end
		reply << "\r\n";
		server.queue_and_send(target_fd, reply.str());
	}
	
	//nick is not valid.
	else{
			std::string my_nick = sender.getNick();
			if (my_nick.empty())
				my_nick = "*";
			reply << ":" << server.getServerName() << " 401 " << my_nick << " " << target << " :No such nick\r\n";
			server.queue_and_send(fd, reply.str());
	}
}

static void	to_channel(std::vector<std::string>& msg, int fd, std::string & target, IRCServ& server){
	//target = target.substr(1); //I need the prefix because #myChannel is different than !myChannel.
	
	//obtain the channels objects from server.
	const std::map<const std::string, IRCChannel>&	channels = server.getChannels();
	std::ostringstream	reply;
	
	//catch sender to have data from him.
	const std::map<int, IRCClient>&	clients	= server.getClients(); //have all the clients
	std::map<int, IRCClient>::const_iterator it_sender = clients.find(fd);
  if (it_sender == clients.end())
    return;    
  const IRCClient &sender = it_sender->second;
	std::string sender_nick = sender.getNick();

	//1. Search for the channel.
	std::map<const string, IRCChannel>::const_iterator it_chan = channels.find(target);
	
	//No channel existence error send
	if (it_chan == channels.end()){
		reply << ":" << server.getServerName() << " 403 " << sender_nick << " "
		<< target << " :No such channel\r\n";
		server.queue_and_send(fd, reply.str());
		return ; 
	}

	//2. Is the sender subscribed to the channel? if not, cannot send privmsg to that channel.
	if (!it_chan->second.checkUser(sender_nick)){
		reply << ":" << server.getServerName() << " 442 " << sender_nick << " " << target
		<< " :You're not member of that channel\r\n";
		server.queue_and_send(fd, reply.str());
		return ;
	}

	//3. Obtain the nicks invited to that channel.
	PairUserMapIterators pairIterators = it_chan->second.getUsersIterators();
	UserMapIterator it_nick = pairIterators.first;
	if (it_nick == pairIterators.second)
		return ;
	const std::map<const std::string, int>& chan_nicks = server.getNicks();
	
	//4. compose msg
	//4a. prefix to send
	reply << ":" << sender_nick << "!" << sender.getUsername() << "@" << sender.getHost() << " PRIVMSG " << target << " :";
	
	//4b. now the msg construction
	std::vector<std::string>::const_iterator it_msg = msg.begin();
	if (it_msg != msg.end())
		it_msg++; //jump over the channel to find the real msg
	for (;it_msg != msg.end(); ++it_msg){
		reply << *it_msg;
		if (it_msg + 1 != msg.end())
			reply << " "; //add separator between words.
	}
	reply << "\r\n";
	
	//5.send to each member except sender.
	for (; it_nick != pairIterators.second; ++it_nick){
		if (sender_nick != it_nick->first){ //only send to nicks different than sender.
			std::map<const std::string, int>::const_iterator it_found = chan_nicks.find(it_nick->first);
			if (it_found != chan_nicks.end()){
				int user_fd = it_found->second;
				server.queue_and_send(user_fd, reply.str());
			}
		}
	}	
}

void IRCServ::answer_privmsg(IRCMessage & msg, int fd) {
	std::ostringstream reply;
	size_t num_params = msg.getParametersSize();
	
	std::string sender_nick = "*";
	std::map<int, IRCClient>::const_iterator it_clients = clients.find(fd);
	if (it_clients != clients.end())
		sender_nick = it_clients->second.getNick();

	
	if (num_params < 1){ //411 ERR_NORECIPIENT
		reply << ":" << server_name << " 411 " << sender_nick << " :No recipient given (PRIVMSG)\r\n";
		queue_and_send(fd, reply.str());
		return ; 
	}
	if (num_params < 2){ //412 ERR_NOTEXTTOSEND
		reply << ":" << server_name << " 412 " << sender_nick <<  " :No text to send (PRIVMSG)\r\n";
		queue_and_send(fd, reply.str());
		return ; 
	}
	
	if (clients.count(fd)){

	std::string 							target = msg.getParam(0);
	std::vector<std::string> 	parameters = msg.getParamsVector();
	if (!target.empty() && (target[0] == '#' || target[0] == '&' || target[0] == '+' || target[0] == '!'))
		to_channel(parameters, fd, target, *this);
	else if (!target.empty())
		to_user(parameters, fd, target, *this);
	}
}

