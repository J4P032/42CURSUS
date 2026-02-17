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

#include "IRCChannel.hpp"
#include "IRCClient.hpp"
#include "IRCCommand.hpp"
#include "IRCServ.hpp"
#include "IRCMessage.hpp"
#include "utils.hpp"
#include <sstream>

/* 
####### nick aaa:
join #tst
:aaa!~AAA@lenovo-i5 JOIN :#tst
:ngircd.none.net 353 aaa = #tst :@aaa
:ngircd.none.net 366 aaa #tst :End of NAMES list
:bbb!~BBB@lenovo-i5 JOIN :#tst
:bbb!~BBB@lenovo-i5 PART #tst :Bye bye

####### nick bbb:
join #tst
:bbb!~BBB@lenovo-i5 JOIN :#tst
:ngircd.none.net 353 bbb = #tst :bbb @aaa
:ngircd.none.net 366 bbb #tst :End of NAMES list
part #tst :Bye bye
:bbb!~BBB@lenovo-i5 PART #tst :Bye bye
*/

void 	IRCServ::answer_part(IRCMessage & msg, int fd) {
  if (msg.getCommand() != CMD_PART || clients.find(fd) == clients.end())
    return;
  IRCClient& client = clients[fd];
  size_t nParams = msg.getParametersSize();
  const string syntaxError = genSyntaxError(server_name, client.getNick(), "PART");
  if (nParams == 0 || nParams > 2) { // not enough parameters
    queue_and_send(fd, syntaxError);
    return;
  }
  vector<string> channelNames = split(msg.getParam(0),",");
  if (channelNames.empty()) {
    queue_and_send(fd, syntaxError);
    return;    
  }
  string byeMsg = (nParams == 2) ? msg.getParam(1) : "user leaving"; 
  for (size_t iChannel=0; iChannel < channelNames.size(); ++iChannel) {
    string chName = channelNames[iChannel];
    ft_toLower(chName);
    if (this->channels.find(chName) == this->channels.end()) {
      // :ngircd.none.net 403 aaa #lalala :No such channel
      std::ostringstream buf;
      buf << ':' << server_name << " 403 " << client.getNick() 
        << ' ' << channelNames[iChannel] << " :No such channel\r\n";
      queue_and_send(client.getFd(), buf.str());
      continue;
    }
    partChannel(*this, client, channels[chName], byeMsg);
  }
}
