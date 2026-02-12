/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer_part.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 13:55:44 by mvassall          #+#    #+#             */
/*   Updated: 2026/02/10 15:29:17 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommand.hpp"
#include "IRCServ.hpp"
#include "IRCMessage.hpp"
#include "utils.hpp"
#include <sstream>
#include <vector>

/* static const string genPartChannel(const IRCClient& client,
    const string& channelName, const string& reason) {
  std::ostringstream oss;
  oss << ':' << client.getNick() 
    << '!' << client.getUsername() 
    << '@' << client.getHost()
    << " PART "
    << channelName;
  if (!reason.empty())
    oss << " :" << reason; 
  oss << "\r\n";
  return oss.str();
}
 */
void 	IRCServ::answer_part(IRCMessage & msg, int fd) {
  if (msg.getCommand() != CMD_PART || clients.count(fd) == 0)
    return;
  IRCClient& client = clients[fd];
  size_t nParams = msg.getParametersSize();
  if (nParams == 0) { // not enough parameters
    queue_and_send(fd,
      genErrNeedMoreParams(server_name, client.getNick()));
    return;
  }
  vector<string> channelNames = split(msg.getParam(0),",");
  if (nParams > 2) {
    
  }
}
