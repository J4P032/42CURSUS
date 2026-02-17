#include "IRCChannel.hpp"
#include "IRCMessage.hpp"
#include "IRCServ.hpp"
#include <sstream>
#include <iostream>
#include <string>

void IRCServ::answer_names(IRCMessage& msg, int fd)
{
    int size = msg.getParametersSize();

    if (size < 1) {
        for (std::map<const std::string, IRCChannel>::iterator it = channels.begin();
            it != channels.end(); ++it)
            this->send_names_from_channel(it->second, fd);
        return;
    }
    vector<string> channelNames = split(msg.getParam(0),",");
    for (size_t i = 0; i < channelNames.size(); i++) {
        std::string channel_name = channelNames[i];
        ft_toLower(channel_name);
        std::map<const std::string, IRCChannel>::iterator it = channels.find(channel_name);
        if (it != channels.end())
            this->send_names_from_channel(it->second, fd);
    }
}

void IRCServ::send_names_from_channel(const IRCChannel& channel, int fd)
{
    std::string client_nick = clients[fd].getNick();
    std::string channel_name = channel.getName();

    std::string prefix = ":" + this->server_name + " 353 " + client_nick + " = " + channel_name + " :";
    std::string buffer = prefix;

    PairUserMapIterators users = channel.getUsersIterators();

    for (UserMapIterator it = users.first; it != users.second; ++it) {
        std::string nick_entry = it->first;

        if (it->second == CHANNEL_OPERATOR)
            nick_entry = "@" + nick_entry;

        // si hay 510 chars enviamos y vaciamos
        if (buffer.length() + nick_entry.length() + 1 > 510) {
            this->queue_and_send(fd, buffer + "\r\n");
            buffer = prefix + nick_entry;
        } else {
            if (buffer != prefix)
                buffer += " ";
            buffer += nick_entry;
        }
    }

    // Enviar lo que quede en el buffer
    if (buffer != prefix)
        this->queue_and_send(fd, buffer + "\r\n");

    std::string end_msg = ":" + this->server_name + " 366 " + client_nick + " " + channel_name + " :End of /NAMES list\r\n";
    this->queue_and_send(fd, end_msg);
}
