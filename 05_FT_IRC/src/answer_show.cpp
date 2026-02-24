/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer_show.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:17:48 by user1             #+#    #+#             */
/*   Updated: 2026/02/17 17:55:58 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCChannel.hpp"
#include "IRCClient.hpp"
#include "IRCMessage.hpp"
#include "IRCServ.hpp"
#include "utils.hpp"
#include <iostream>
#include <ostream>

static void show_channel(IRCServ& ircServer, const string& name) {
  map<string,IRCChannel>::const_iterator it = ircServer.getChannels().find(name);
  if (it == ircServer.getChannels().end()) {
    std::cerr << "SHOW " << name << " : No such channel" << std::endl;
    return;
  }
  std::cerr << "Channel: " << it->second.toString() << std::endl;
}

static void show_user(IRCServ& ircServer, const string& name) {
  map<string,int>::const_iterator nicksIt = ircServer.getNicks().find(name);
  if (nicksIt == ircServer.getNicks().end()) {
    std::cerr << "SHOW " << name << " : No such nick" << std::endl;
    return;
  }
  map<int,IRCClient>::const_iterator clientsIt = ircServer.getClients().find(nicksIt->second);
  if (clientsIt == ircServer.getClients().end()) {
    std::cerr << "SHOW " << name << " : No such client" << std::endl;
    return;
  }
  std::cerr << "Client: " << clientsIt->second.toString() << std::endl;
}

void IRCServ::answer_show(IRCMessage& msg, int fd) {
  (void)fd;
  if (msg.getParametersSize() == 0) {
    std::cerr << "SHOW: empty name" << std::endl;
    return;
  }
  for (size_t i=0; i < msg.getParametersSize(); ++i) {
    string name = msg.getParam(i);
    ft_toLower(name);
    const static string CHANNEL_PREFIX = "#&+!";
    if (CHANNEL_PREFIX.find_first_of(name[0]) != std::string::npos) {
      show_channel(*this, name);
    } else {
      show_user(*this, name);
    }
  }
}
