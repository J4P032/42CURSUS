/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer_notice.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:02:01 by jrollon-          #+#    #+#             */
/*   Updated: 2026/02/10 17:15:51 by jrollon-         ###   ########.fr       */
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

	//3. construct the reply msg format: :nick!user@host NOTICE target :message.
	if (it_target != nicks.end()) {
    int target_fd = it_target->second;
		
		//the prefix
		reply << ":" << sender.getNick() << "!" << sender.getUsername() << "@" << sender.getHost() << " NOTICE " << target << " :";

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
	

	//2. Obtain the nicks invited to that channel.
	if (it_chan != channels.end()){
		PairUserMapIterators pairIterators = it_chan->second.getUsersIterators();
		UserMapIterator it_nick = pairIterators.first;
		if (it_nick == pairIterators.second)
			return ;
		const std::map<const std::string, int>& chan_nicks = server.getNicks();
	
	
		//3. compose msg
		//3a. prefix to send
		reply << ":" << sender_nick << "!" << sender.getUsername() << "@" << sender.getHost() << " NOTICE " << target << " :";
	
		//3b. now the msg construction
		std::vector<std::string>::const_iterator it_msg = msg.begin();
		if (it_msg != msg.end())
			it_msg++; //jump over the channel to find the real msg
		for (;it_msg != msg.end(); ++it_msg){
			reply << *it_msg;
			if (it_msg + 1 != msg.end())
				reply << " "; //add separator between words.
		}
		reply << "\r\n";
	
		//4.send to each member except sender.
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
	else
		return;
}

void IRCServ::answer_notice(IRCMessage & msg, int fd) {
	std::ostringstream reply;
	size_t num_params = msg.getParametersSize();
	
	if (num_params < 2)
		return ;

	if (clients.count(fd)){
		std::string 							target = msg.getParam(0);
		std::vector<std::string> 	parameters = msg.getParamsVector();
		if (!target.empty() && (target[0] == '#' || target[0] == '&' || target[0] == '+' || target[0] == '!'))
			to_channel(parameters, fd, target, *this);
		else if (!target.empty())
			to_user(parameters, fd, target, *this);
	}
}
