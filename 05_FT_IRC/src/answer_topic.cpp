#include "IRCChannel.hpp"
#include "IRCMessage.hpp"
#include "IRCServ.hpp"
#include "utils.hpp"
#include <string>

void IRCServ::answer_topic(IRCMessage& msg, int fd)
{
    std::string nick = clients[fd].getNick();
    // ERROR 461
    if (msg.getParametersSize() < 1) {
        std::string err = ":" + server_name + " 461 " + nick + " TOPIC :Not enough parameters\r\n";
        queue_and_send(fd, err);
        return;
    }
    std::string ch_name = msg.getParam(0);
    ft_toLower(ch_name);
    std::map<const std::string, IRCChannel>::iterator it = channels.find(ch_name);
    // ERROR 403
    if (it == channels.end()) {
        std::string err = ":" + server_name + " 403 " + nick + " " + ch_name + " :No such channel\r\n";
        queue_and_send(fd, err);
        return;
    }

    IRCChannel & channel = it->second;
    if (!channel.checkUser(nick))
    	{queue_and_send(fd, ":" + server_name + " 442 " + nick + " " + ch_name + " :You're not on that channel\r\n"); return;}

    if (msg.getParametersSize() > 1) 
    {
        if (channel.checkChannelMode(TOPIC) && channel.getUserMode(nick) != CHANNEL_OPERATOR) 
        	{queue_and_send(fd, ":" + server_name + " 482 " + nick + " " + ch_name + " :You're not channel operator\r\n"); return;}
        std::string new_topic = msg.getParam(1);
        channel.setTopic(nick, new_topic);

        std::string alert = ":" + nick + "!" + clients[fd].getUsername() + "@" + clients[fd].getHost() 
                          + " TOPIC " + ch_name + " :" + new_topic + "\r\n";
        broadcastToChannel(channel, alert);
    }
    else
    {
        std::string current_topic = channel.getTopic();
        if (current_topic.empty())
            queue_and_send(fd, ":" + server_name + " 331 " + nick + " " + ch_name + " :No topic is set\r\n");
        else 
            queue_and_send(fd, ":" + server_name + " 332 " + nick + " " + ch_name + " :" + current_topic + "\r\n");
    }
}

void IRCServ::broadcastToChannel(IRCChannel & channel, const std::string & message)
{
    PairUserMapIterators users = channel.getUsersIterators();

    for (UserMapIterator it = users.first; it != users.second; ++it) {
        std::map<const std::string, int>::iterator target_fd = nicks.find(it->first);
        if (target_fd != nicks.end())
            queue_and_send(target_fd->second, message);
    }
}
