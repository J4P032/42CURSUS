#include "IRCClient.hpp"
#include "IRCCommand.hpp"
#include "IRCMessage.hpp"
#include "IRCServ.hpp"
#include "IRCChannel.hpp"
#include <sstream>
#include <string>
#include <vector>

void IRCServ::answer_topic(IRCMessage & msg, int fd)
{
		std::string nick = clients[fd].getNick();
		// ERROR 461
		if (msg.getParametersSize() < 1) 
		{
				std::string err = ":" + server_name + " 461 " + nick + " TOPIC :Not enough parameters\r\n";
				queue_and_send(fd, err);
				return;
		}
		std::string ch_name = msg.getParam(0);
		std::map<const std::string, IRCChannel>::iterator it = channels.find(ch_name);
		// ERROR 403
		if (it == channels.end()) 
		{
				std::string err = ":" + server_name + " 403 " + nick + " " + ch_name + " :No such channel\r\n";
				queue_and_send(fd, err);
				return;
		}

		IRCChannel & channel = it->second;
		if (msg.getParametersSize() > 1) 
		{
				std::string new_topic = msg.getParam(1);
				channel.setTopic(nick, new_topic);
				std::string alert = ":" + nick + "!" + clients[fd].getUsername() + "@" + clients[fd].getHost() 
													+ " TOPIC " + ch_name + " :" + new_topic + "\r\n";
				this->broadcastToChannel(channel, alert);
		}
		else
		{
				std::string current_topic = channel.getTopic();
				if (current_topic.empty())
					queue_and_send(fd, ":" + server_name + " 331 " + nick + " " + ch_name + " :No topic is set\r\n");
					// RPL_NOTOPIC (331)
				else 
					queue_and_send(fd, ":" + server_name + " 332 " + nick + " " + ch_name + " :" + current_topic + "\r\n");
					// RPL_TOPIC (332)
		}
}


void IRCServ::broadcastToChannel(IRCChannel & channel, const std::string & message)
{
    PairUserMapIterators users = channel.getUsersIterators();

    for (UserMapIterator it = users.first; it != users.second; ++it)
    {
        std::map<const std::string, int>::iterator target_fd = nicks.find(it->first); 
        if (target_fd != nicks.end())
            queue_and_send(target_fd->second, message);
    }
}
