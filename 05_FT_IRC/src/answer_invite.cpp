/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer_invite.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:42:05 by mvassall          #+#    #+#             */
/*   Updated: 2026/02/17 19:16:22 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCChannel.hpp"
#include "IRCClient.hpp"
#include "IRCCommand.hpp"
#include "IRCServ.hpp"
#include "utils.hpp"
#include <iostream>
#include <sstream>

/*
nick aaa:
invite bbb #tst
:ngircd.none.net 341 aaa bbb #tst
invite bbb #tst
:ngircd.none.net 341 aaa bbb #tst
:bbb!~BBB@lenovo-i5 JOIN :#tst
invite bbb #tst
:ngircd.none.net 443 aaa bbb #tst :is already on channel


nick bbb:
:aaa!~AAA@lenovo-i5 INVITE bbb #tst
invite ccc #tst
:ngircd.none.net 482 bbb #tst :You are not channel operator
invite ddd #tst
:ngircd.none.net 401 bbb ddd :No such nick or channel name


nick ccc:
invite
:ngircd.none.net 461 ccc invite :Syntax error
invite aaa
:ngircd.none.net 461 ccc invite :Syntax error
invite 89
:ngircd.none.net 461 ccc invite :Syntax error

invite aaa #tst
:ngircd.none.net 442 ccc #tst :You are not on that channel
*/

static string noSuchNickOrChannel(const string& serverName, const string& invitingNickName, const string& channelName) {
  std::ostringstream buf;
  buf << ':' << serverName << " 401 " << invitingNickName << ' ' << channelName
    << " :No such nick or channel name\r\n";
  return buf.str();
}

static string notInChannel(const string& serverName, const string& invitingNickName, const string& channelName) {
  std::ostringstream buf;
  buf << ':' << serverName << " 442 " << invitingNickName << ' ' << channelName
    << " :You are not on that channel\r\n";
  return buf.str();
}

static string alreadInChannel(const string& serverName,
  const string& invitingNickName,
  const string& invitedNickName,
  const string& invitedChannelName) {
  std::ostringstream buf;
  buf << ':' << serverName
    << " 443 " << invitingNickName
    << ' ' << invitedNickName
    << ' ' << invitedChannelName << " :is already on channel/r/n";
  return buf.str();
}

static string notChannelOperator(const string& serverName, const string& invitingNick, const string& channelName) {
  std::ostringstream buf;
  buf << ':' << serverName << " 482 " << invitingNick << ' ' << channelName
    << " :You are not channel operator\r\n";
  return buf.str();
}

void			IRCServ::answer_invite(IRCMessage& msg, int invitingFd) {
  if (msg.getCommand() != CMD_INVITE || clients.find(invitingFd) == clients.end())
      return;
  IRCClient invitingClient = clients[invitingFd];
  if (msg.getParametersSize() != 2) {
    queue_and_send(invitingFd, genSyntaxError(server_name, invitingClient.getNick(), "invite"));
    return ;
  }
  string invitedNickName = msg.getParam(0);
  string invitedChannelName = msg.getParam(1);
  if (!IRCClient::isValidNick(invitedNickName)
    || !IRCChannel::isValidName(invitedChannelName)) {
    queue_and_send(invitingFd, genSyntaxError(server_name, invitingClient.getNick(), "invite"));
    return ;    
  }
  ft_toLower(invitedNickName);
  ft_toLower(invitedChannelName);
  if (nicks.find(invitedNickName) == nicks.end()
    || channels.find(invitedChannelName) == channels.end()) {
    queue_and_send(invitingFd, noSuchNickOrChannel(server_name, invitingClient.getNick(), invitedChannelName));
    return;
  }
  if (!invitingClient.checkChannel(invitedChannelName)) {
    queue_and_send(invitingFd, notInChannel(server_name, invitingClient.getNick(), invitedChannelName));
    return ;
  }
  IRCChannel invitedChannel = channels[invitedChannelName];
  IRCClient invitedClient = clients[nicks[invitedNickName]];
  if (invitedChannel.checkUser(invitedClient.getNick())) {
    queue_and_send(invitingFd, alreadInChannel(server_name, invitingClient.getNick(), invitedNickName, invitedChannelName));
    return;
  }
  if (invitedChannel.checkChannelMode(INVITE_ONLY) 
    && (invitedChannel.getUserMode(invitingClient.getNick()) != CHANNEL_OPERATOR)) {
    queue_and_send(invitingFd, notChannelOperator(server_name, invitingClient.getNick(), invitedChannelName));
    return;
  }
  invitedChannel.addInvitedNick(invitedNickName);
  channels[invitedChannelName] = invitedChannel;
  string invitingReply = ":" + server_name + " 341 " + invitingClient.getNick()
    + ' ' + invitedNickName + ' ' + invitedChannelName + "\r\n";
  queue_and_send(invitingFd, invitingReply);
  string invitedMsg = ":" + invitingClient.getNick() 
    + '!' + invitingClient.getUsername() + '@' + invitingClient.getHost()
    + " INVITE " + invitedNickName + ' ' + invitedChannelName + "\r\n";
  queue_and_send(invitedClient.getFd(), invitedMsg);
}
