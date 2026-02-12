/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer_join.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:42:05 by mvassall          #+#    #+#             */
/*   Updated: 2026/02/10 15:29:05 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCClient.hpp"
#include "IRCCommand.hpp"
#include "IRCMessage.hpp"
#include "IRCServ.hpp"
#include "IRCChannel.hpp"
#include <sstream>
#include <string>
#include <vector>


static void join0(const IRCClient& client, int fd) {
  (void)client;
  (void)fd;
/*   pairIterators clientChIts = client.getChannelIterators();
  std::ostringstream oss; // append all channel names separated with ','
  for (setOfStringsIterator chIt = clientChIts.first;
    chIt != clientChIts.second; ++chIt) {
    if (chIt != clientChIts.first) oss << ',';
    oss << *chIt;
  }
  vector<string> params;
  params.push_back(oss.str());
  IRCMessage msg("", CMD_PART, params);
  answer_part(msg, fd); */
  return;   
}

/*
join lalala
:ngircd.none.net 403 n01 lalala :No such channel
*/
static string genNoSuchChannel(const string& servername,
  const string& nick, const string& channelName) {
  std::ostringstream oss;
  oss << ':' << servername 
    << ' ' << IRCCommandtoString(ERR_NOSUCHCHANNEL)
    << ' ' << nick
    << ' ' << channelName
    << " :No such channel\r\n";
  return oss.str();
}

/* Creating a new channel
>> join #test
:n01!~user1@lenovo-i5 JOIN :#test
:ngircd.none.net 353 n01 = #test :@n01
:ngircd.none.net 366 n01 #test :End of NAMES list
*/

// static void createNewChannel() {
  
// }
/* Joining an already existing channel
>> join #test

:n02!~user2@lenovo-i5 JOIN :#test
:ngircd.none.net 332 n02 #test :Channel usage # RPL_TOPIC
:ngircd.none.net 333 n02 #test n01 1770644364 # Undef in RFC2812
:ngircd.none.net 353 n02 = #test :n02 @n01    #  RPL_NAMREPLY
:ngircd.none.net 366 n02 #test :End of NAMES list # RPL_ENDOFNAMES
*/
//  
void  IRCServ::answer_join(IRCMessage& msg, int fd) {
  if (msg.getCommand() != CMD_JOIN || clients.count(fd) == 0)
    return;
  IRCClient& client = clients[fd];
  size_t nParams = msg.getParametersSize();
  if (nParams == 0) { // not enough parameters
    queue_and_send(fd,
      genErrNeedMoreParams(server_name, client.getNick()));
    return;
  }
  string param0 = msg.getParam(0);
  if (nParams == 1) {
    if (param0 == "0") { // user leaves all channels
      join0(client, fd);
      return;
    }
    // a list of channels
    vector<string> channelNames = split(param0, ",");
    if (channelNames.empty()) {
      queue_and_send(fd,
      genErrNeedMoreParams(server_name, client.getNick()));
      return;      
    }
    for (size_t i=0; i < channelNames.size(); ++i) {
      if (!IRCChannel::isValidName(channelNames[i])) {
        queue_and_send(fd, 
          genNoSuchChannel(server_name, client.getNick(),
          channelNames[i]));
        return;
      }
      // name is valid, is it new?
      if (channels.count(channelNames[i]) == 0) {
        
      }
    }
  }
  
}

