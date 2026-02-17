#include "IRCChannel.hpp"
#include "IRCMessage.hpp"
#include "IRCServ.hpp"
#include "utils.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>

void IRCServ::answer_mode(IRCMessage & msg, int fd) {
    IRCClient &client = clients[fd];
    std::string nick = client.getNick();
    std::string server = getServerName();

    if (msg.getParametersSize() < 1) {
        queue_and_send(fd, ":" + server + " 461 " + nick + " MODE :Not enough parameters\r\n");
        return;
    }

    std::string target = msg.getParam(0);
    // ----- MODO USUARIO -----
    if (target[0] != '#' && target[0] != '&' && target[0] != '+' && target[0] != '!') {
        if (target != nick)
            queue_and_send(fd, ":" + server + " 502 " + nick + " :Cant change mode for other users\r\n");
        return;
    }

    // ----- MODO CANAL -----
    if (channels.find(target) == channels.end()) {
        queue_and_send(fd, ":" + server + " 403 " + nick + " " + target + " :No such channel\r\n");
        return;
    }

    IRCChannel& channel = channels[target];

    // CASO: Consulta de modos (Solo 1 parámetro)
    if (msg.getParametersSize() == 1) {
        std::string modes = "";
        const std::set<ChannelMode>& modesSet = channel.getChannelModes();
        for (std::set<ChannelMode>::const_iterator it = modesSet.begin(); it != modesSet.end(); ++it)
            modes += channelModeToString(*it);
        
        // El 324 está bien porque son todo strings
        queue_and_send(fd, ":" + server + " 324 " + nick + " " + target + " +" + modes + "\r\n");
        
        // CORRECCIÓN PARA EL 329 (Creation Time es un número)
        std::stringstream ss;
        ss << ":" << server << " 329 " << nick << " " << target << " " << channel.getCreationTime() << "\r\n";
        queue_and_send(fd, ss.str());
        return;
    }

    // Verificaciones de permisos
    if (!channel.checkUser(nick)) {
        queue_and_send(fd, ":" + server + " 442 " + nick + " " + target + " :You're not on that channel\r\n");
        return;
    }
    if (channel.getUserMode(nick) != CHANNEL_OPERATOR) {
        queue_and_send(fd, ":" + server + " 482 " + nick + " " + target + " :You're not channel operator\r\n");
        return;
    }

    std::string flags = msg.getParam(1);
    std::string prefix = ":" + nick + "!" + client.getUsername() + "@" + client.getHost();
    bool is_neg = false;
    unsigned int arg_idx = 2;

    for (size_t i = 0; i < flags.length(); ++i) {
        char flag = flags[i];
        if (flag == '+') { is_neg = false; continue; }
        if (flag == '-') { is_neg = true; continue; }

        std::string param = "";
        std::string rpl_flag = (is_neg ? "-" : "+");
        rpl_flag += flag;

        switch(flag) {
            case 'i': is_neg ? channel.unsetChannelMode(INVITE_ONLY) : channel.setChannelMode(INVITE_ONLY); break;
            case 't': is_neg ? channel.unsetChannelMode(TOPIC) : channel.setChannelMode(TOPIC); break;
            case 'k':
                if (is_neg) { channel.unsetChannelMode(KEY); channel.setKey(""); }
                else if (msg.getParametersSize() > arg_idx) {
                    param = msg.getParam(arg_idx++);
                    channel.setChannelMode(KEY); channel.setKey(param);
                } else { queue_and_send(fd, ":" + server + " 461 " + nick + " MODE :+k needs param\r\n"); continue; }
                break;
            case 'l':
                if (is_neg) { channel.unsetChannelMode(USER_LIMIT); }
                else if (msg.getParametersSize() > arg_idx) {
                    param = msg.getParam(arg_idx++);
                    channel.setChannelMode(USER_LIMIT); channel.setUserLimit(std::atoi(param.c_str()));
                } else { queue_and_send(fd, ":" + server + " 461 " + nick + " MODE :+l needs param\r\n"); continue; }
                break;
            case 'o':
                if (msg.getParametersSize() > arg_idx) {
                    param = msg.getParam(arg_idx++);
                    if (!channel.checkUser(param)) {
                        queue_and_send(fd, ":" + server + " 441 " + nick + " " + param + " " + target + " :Not on channel\r\n");
                        continue;
                    }
                    channel.setUserMode(param, is_neg ? USER_ONLY : CHANNEL_OPERATOR);
                } else { queue_and_send(fd, ":" + server + " 461 " + nick + " MODE :+/-o needs param\r\n"); continue; }
                break;
            default:
                queue_and_send(fd, ":" + server + " 472 " + nick + " " + flag + " :is unknown mode char\r\n");
                continue;
        }
        // Broadcast de la acción exitosa
        broadcastToChannel(channel, prefix + " MODE " + target + " " + rpl_flag + (param.empty() ? "" : " " + param) + "\r\n");
    }
}
