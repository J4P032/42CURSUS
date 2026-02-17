#include <cstdlib>
#include "IRCServ.hpp"
#include "IRCMessage.hpp"
#include "IRCClient.hpp"
#include "IRCChannel.hpp"
#include <sstream>
#include <iostream>

void IRCServ::answer_mode(IRCMessage & msg, int fd) {
	if (msg.getParametersSize() < 1) {
		// ERR_NEEDMOREPARAMS
		std::string rpl = ":" + this->getServerName() + " 461 " + clients[fd].getNick() + " MODE :Not enough parameters\r\n";
		queue_and_send(fd, rpl);
		return;
	}

	std::string target = msg.getParam(0);
	std::string flags;
	if (msg.getParametersSize() != 1) 
		flags = msg.getParam(1);

	if (target[0] == '#' || target[0] == '&' || target[0] == '+' || target[0] == '!') {
		// ----- MODO CANAL -----
		if (channels.find(target) == channels.end()) {
			// ERR_NOSUCHCHANNEL
			std::string rpl = ":" + this->getServerName() + " 403 " + clients[fd].getNick() + " " + target + " :No such channel\r\n";
			queue_and_send(fd, rpl);
			return;
		}
		IRCChannel& channel = channels[target];
		if (msg.getParametersSize() == 1)
		{

			std::string nick = clients[fd].getNick();
			std::string server = this->getServerName();

			string modes = "";
			const set<ChannelMode>& modesSet = channel.getChannelModes();

			for (set<ChannelMode>::const_iterator it = modesSet.begin(); it != modesSet.end(); ++it)
					modes += channelModeToString(*it);
			std::stringstream rpl324;
			rpl324 << ":" << server << " 324 " << nick << " " << target << " +" 
						<< modes << "\r\n";

			queue_and_send(fd, rpl324.str());

			std::stringstream rpl329;
			rpl329 << ":" << server << " 329 " << nick << " " << target << " " 
						<< channel.getCreationTime() << "\r\n";

			queue_and_send(fd, rpl329.str());

			std::cout << channel.toString() << std::endl;
			return;
		}

		if (!channel.checkUser(clients[fd].getNick())) {
			// ERR_NOTONCHANNEL
			std::string rpl = ":" + this->getServerName() + " 442 " + clients[fd].getNick() + " " + target + " :You're not on that channel\r\n";
			queue_and_send(fd, rpl);
			return;
		}

		if (channel.getUserMode(clients[fd].getNick()) != CHANNEL_OPERATOR) {
			// ERR_CHANOPRIVSNEEDED
			std::string rpl = ":" + this->getServerName() + " 482 " + clients[fd].getNick() + " " + target + " :You're not channel operator\r\n";
			queue_and_send(fd, rpl);
			return;
		}

		bool is_flag_neg;
		unsigned int arg_idx = 2;

		for (size_t i = 0; i < flags.length(); ++i) {
			char flag = flags[i];
			if (flag == '+') {
				is_flag_neg = false;
				continue;
			}
			if (flag == '-') {
				is_flag_neg = true;
				continue;
			}

			switch(flag) {
				case 'i':
					if (is_flag_neg)
						channel.unsetChannelMode(INVITE_ONLY);
					else
						channel.setChannelMode(INVITE_ONLY);
					break;
				case 't':
					if (is_flag_neg)
					{
						channel.unsetChannelMode(TOPIC);
						channel.setTopic(clients[fd].getNick(), "");
					}
					else
					{
						if (msg.getParametersSize() <= arg_idx) {
							// ERR_NEEDMOREPARAMS
							std::string rpl = ":" + this->getServerName() + " 461 " + clients[fd].getNick() + " MODE :Not enough parameters for +k\r\n";
							queue_and_send(fd, rpl);
							break; 
						}
						channel.setChannelMode(TOPIC);
						channel.setTopic(clients[fd].getNick(), msg.getParam(arg_idx));
					}
					break;
				case 'k':
					if (is_flag_neg) {
						channel.unsetChannelMode(KEY);
						channel.setKey("");
					} else {
						if (msg.getParametersSize() <= arg_idx) {
							// ERR_NEEDMOREPARAMS
							std::string rpl = ":" + this->getServerName() + " 461 " + clients[fd].getNick() + " MODE :Not enough parameters for +k\r\n";
							queue_and_send(fd, rpl);
							break; 
						}
						channel.setChannelMode(KEY);
						channel.setKey(msg.getParam(arg_idx));
						arg_idx++;
					}
					break;
				case 'o': {
					if (msg.getParametersSize() <= arg_idx) {
						// ERR_NEEDMOREPARAMS
						std::string rpl = ":" + this->getServerName() + " 461 " + clients[fd].getNick() + " MODE :Not enough parameters for +/-o\r\n";
						queue_and_send(fd, rpl);
						break; 
					}
					std::string user_nick = msg.getParam(arg_idx);
					if (!channel.checkUser(user_nick)) {
						// ERR_USERNOTINCHANNEL
						std::string rpl = ":" + this->getServerName() + " 441 " + clients[fd].getNick() + " " + user_nick + " " + target + " :They aren't on that channel\r\n";
						queue_and_send(fd, rpl);
						break;
					}
					channel.setUserMode(user_nick, is_flag_neg ? USER_ONLY : CHANNEL_OPERATOR);
					arg_idx++;
					break;
				}
				case 'l':
					if (is_flag_neg) {
						channel.unsetChannelMode(USER_LIMIT);
					} else {
						if (msg.getParametersSize() <= arg_idx) {
							// ERR_NEEDMOREPARAMS
							std::string rpl = ":" + this->getServerName() + " 461 " + clients[fd].getNick() + " MODE :Not enough parameters for +l\r\n";
							queue_and_send(fd, rpl);
							break;
						}
						channel.setChannelMode(USER_LIMIT);
						channel.setUserLimit(std::atoi(msg.getParam(arg_idx).c_str()));
						arg_idx++;
					}
					break;
				default: {
					// ERR_UNKNOWNMODE
					std::ostringstream char_to_str;
					char_to_str << flag;
					std::string rpl = ":" + this->getServerName() + " 472 " + clients[fd].getNick() + " " + char_to_str.str() + " :is unknown mode char to me for " + target + "\r\n";
					queue_and_send(fd, rpl);
					break;
				}
			}
		}
	} else {
		// ----- MODO USUARIO -----
		// Aquí solo gestionamos si el target es el propio usuario que ejecuta el comando.
		if (target != clients[fd].getNick()) {
			// ERR_USERSDONTMATCH
			std::string rpl = ":" + this->getServerName() + " 502 " + clients[fd].getNick() + " :Cant change mode for other users\r\n";
			queue_and_send(fd, rpl);
			return;
		}
	}
}

