/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer_kick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:17:10 by jrollon-          #+#    #+#             */
/*   Updated: 2026/02/17 14:44:25 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommand.hpp"
#include "IRCServ.hpp"
#include <sstream>

typedef std::map<int, IRCClient>::iterator SENDER;

void	removeClientFromChannel(const std::vector<std::string>& parameters, IRCClient& sender, std::string victim, IRCChannel& my_channel, IRCServ& server){
	std::ostringstream 	reply;
	int									victim_fd;

	//compose reply msg to all users on the channel.
	reply << ":" << sender.getNick() << "!" << sender.getUsername() << "@" << sender.getHost() << " KICK "
	<< my_channel.getName() << " " << victim << " :";
	for (size_t i = 2; i < parameters.size(); ++i){	
		reply << parameters[i];
		if (i + 1 != parameters.size())
			reply << " ";	
	}
	if (parameters.size() == 2)
		reply << sender.getNick();
	reply << "\r\n";

	//send to all users of the channel.
	server.broadcastToChannel(my_channel, reply.str());

	//remove the user from the channel
	my_channel.delUser(victim);

	//remove the channel from the victim IRCClient
	std::map<int, IRCClient>&	clients	= server.getClients();
	const std::map<const std::string, int>& nicks = server.getNicks();
	std::map<const std::string, int>::const_iterator it_nicks = nicks.find(victim);
	if (it_nicks != nicks.end())
		victim_fd = it_nicks->second;
	else
		return ;
	std::map<int, IRCClient>::iterator it_clients = clients.find(victim_fd);
	if (it_clients != clients.end())
		it_clients->second.delChannel(my_channel.getName());
}


void IRCServ::answer_kick(IRCMessage & msg, int fd) {
	std::ostringstream reply;
	
	//find the sender of KICK and pick his data.
	SENDER it_sender = clients.find(fd);
	if (it_sender == clients.end())
		return ;
	IRCClient sender = it_sender->second;
	std::string	sender_nick = sender.getNick();
	ft_toLower(sender_nick); 
	

	//check number of parameters
	const std::vector<std::string>& parameters = msg.getParamsVector();
	size_t param_number = parameters.size();
	if (param_number < 2){
		reply << ":" << getServerName() << " 461 " << sender_nick << " KICK " << ":Not enough parameters\r\n";
		queue_and_send(fd, reply.str());
		return ;
	}
		
	//check name of the channel the kick was sent. It will be include automatically or the client can write it outside of it
	std::vector<std::string>::const_iterator it_param = parameters.begin();
	std::string	kick_channel_name = *it_param;
	ft_toLower(kick_channel_name);
	
	//check if the channel exist in server
	std::map<const string, IRCChannel>& server_channels = getChannels();
	std::map<const string, IRCChannel>::iterator it_server_channels = server_channels.find(kick_channel_name);
	if (it_server_channels == server_channels.end()){ //not found in server channels
		reply << ":" << getServerName() << " 403 " << sender_nick << " " << kick_channel_name << " :No such channel\r\n"; 
		queue_and_send(fd, reply.str());
		return ;
	}
	
	//Check if sender of KICK is in that channel.
	const std::set<std::string>& channels_subscribed = sender.getChannelNames();
	std::set<std::string>::const_iterator it_chan_sub = channels_subscribed.find(kick_channel_name);
	if (it_chan_sub == channels_subscribed.end()){
		reply << ":" << getServerName() << " 442 " << sender_nick << " " << kick_channel_name <<  ":You're not on that channel\r\n"; 
		queue_and_send(fd, reply.str());
		return ;
	}
	
	//Check if the user is operator of that channel.
	IRCChannel&	kick_channel = it_server_channels->second;	
	UserMode mode = kick_channel.getUserMode(sender_nick);
	if (mode == UNDEF){
		reply << ":" << getServerName() << " 442 " << sender_nick << " " << kick_channel_name <<  ":You're not on that channel\r\n"; 
		queue_and_send(fd, reply.str());
		return ;
	}
	if (mode != CHANNEL_OPERATOR){
		reply << ":" << getServerName() << " 482 " << sender_nick << " " << kick_channel_name <<  ":You're not channel operator\r\n"; 
		queue_and_send(fd, reply.str());
		return ;
	}

	//check name of the KICK victim and see if he is in the channel. Can send a list of victims separated with comma
	std::stringstream	victim_list(parameters[1]);
	std::string	victim;
	UserMode victim_mode;
	while (std::getline(victim_list, victim, ',')){
		if (victim.empty()) 
			continue;
		reply.str("");
		reply.clear();
		ft_toLower(victim); 
		victim_mode = kick_channel.getUserMode(victim);
		if (victim_mode != UNDEF)
			removeClientFromChannel(parameters, sender, victim, kick_channel, *this);
		else {
			reply << ":" << getServerName() << " 441 " << sender_nick << " " << victim << " " << kick_channel_name << " :They aren't on that channel\r\n";
			queue_and_send(fd, reply.str());
		}	
	}
	
	//if empty of users because autokick then remove it from server.
	if (kick_channel.getNumberOfUsers() == 0)
		delEmptyChannel(kick_channel_name);
}
