/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer_join.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:42:05 by mvassall          #+#    #+#             */
/*   Updated: 2026/02/16 10:32:02 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCClient.hpp"
#include "IRCCommand.hpp"
#include "IRCMessage.hpp"
#include "IRCServ.hpp"
#include "IRCChannel.hpp"
#include "utils.hpp"
#include <sstream>
#include <string>

/*
join lalala
:ngircd.none.net 403 n01 lalala :No such channel
*/
static string genNoSuchChannel(const string& servername,
  const string& nick, const string& channelName) {
  std::ostringstream oss;
  oss << ':' << servername << " 403 " << nick << ' ' << channelName
    << " :No such channel\r\n";
  return oss.str();
}

/*
===== n001
join #test
:n001!~User1@10.0.2.2 JOIN :#test
:ngircd.none.net 353 n001 = #test :@n001
:ngircd.none.net 366 n001 #test :End of NAMES list
topic #test :test of topic
:n001!~User1@10.0.2.2 TOPIC #test :test of topic

:n002!~User2@10.0.2.2 JOIN :#test
:n003!~User3@10.0.2.2 JOIN :#test

====== n003
join #test
:n003!~User3@10.0.2.2 JOIN :#test
:ngircd.none.net 332 n003 #test :test of topic
:ngircd.none.net 333 n003 #test n001 1770819078
:ngircd.none.net 353 n003 = #test :n003 n002 @n001
:ngircd.none.net 366 n003 #test :End of NAMES list
*/

// :n02!~user2@lenovo-i5 JOIN :#test
static string genJoinReply(const IRCClient& ircClient, const string& channelName) {
  std::ostringstream buf;
  buf << ':' << ircClient.getNick() 
  << '!' << ircClient.getUsername()
  << '@' << ircClient.getHost()
  << " JOIN :" << channelName << "\r\n";
  return buf.str();
}

// :ngircd.none.net 332 n02 #test :Channel usage # RPL_TOPIC
static string genTopicReply(const string& serverName, const string& nick, const IRCChannel& ircChannel) {
  std::ostringstream buf; 
  buf << ':' << serverName
    << " 332 " << nick
    << ' ' << ircChannel.getName()
    << " :" << (ircChannel.getTopic().empty()? "Topic not set" : ircChannel.getTopic())
    << "\r\n";
  return buf.str();
}

// :ngircd.none.net 333 n02 #test n01 1770644364 # Undef in RFC2812
static string genCreationTimeReply(const string& serverName, const string& nick, const IRCChannel& ircChannel) {
  std::ostringstream buf; 
  buf << ':' << serverName
    << " 333 " << nick
    << ' ' << ircChannel.getName()
    << ' ' << ircChannel.getCreatorNick()
    << ' ' << ircChannel.getCreationTime()
    << "\r\n";
  return buf.str();
}

//:ngircd.none.net 353 n003 = #test :n003 n002 @n001
static string genMemberReply(const string& server_name, const string& jNick, 
  const string& channelName, const UserMode mUserMode, const string& mNick) {
  std::ostringstream buf;
  buf << ':' << server_name 
    << " 353 " << jNick
    << " = " << channelName << " :";
  if (mUserMode == CHANNEL_OPERATOR) buf << '@';
  buf << mNick << "\r\n";
  return buf.str();
}

// :ngircd.none.net 366 n003 #test :End of NAMES list
static string genEndList(const string& server_name, const string& jNick,
  const string& channelName) {
  std::ostringstream buf;
  buf << server_name << " 366 " << jNick << ' ' << channelName 
    << " :End of NAMES list\r\n";
  return buf.str();
}

void  IRCServ::answer_join(IRCMessage& msg, int fd) {
  if (msg.getCommand() != CMD_JOIN || clients.find(fd) == clients.end())
    return;
  IRCClient& jClient = clients[fd];   // IRCClient of the JOIN issuer
  size_t nParams = msg.getParametersSize();
  if (nParams == 0 || nParams > 2) { // Syntax error
    queue_and_send(fd,
      genSyntaxError(server_name, jClient.getNick(),"JOIN"));
    return;
  }
  if (nParams == 1 && msg.getParam(0) == "0") { // join 0
    if (jClient.getChannelNames().empty()) return;
      const std::set<std::string>& channelNames = jClient.getChannelNames();
      for (std::set<std::string>::const_iterator chNameIt = channelNames.begin();
        chNameIt != channelNames.end(); ++chNameIt) {
        if (channels.find(*chNameIt) == channels.end()) continue;
        IRCChannel ircChannel = channels[*chNameIt];
        partChannel(*this, jClient, ircChannel, "");
      }
    return;
  }
  // a list of channels
  vector<string> channelNames = split(msg.getParam(0), ",");
  if (channelNames.empty()) {
    queue_and_send(fd,
    genSyntaxError(server_name, jClient.getNick(),"JOIN"));
    return;      
  }
  vector<string> channelKeys;
  if (nParams == 2) channelKeys = split(msg.getParam(1),",");
  for (size_t i=0; i < channelNames.size(); ++i) { // iterate over all requested channels
    string channelName = channelNames[i];
    ft_toLower(channelName); // IRC channel names are case-insensitive
    if (!IRCChannel::isValidName(channelName)) {
      string rp = genNoSuchChannel(server_name, jClient.getNick(), channelName);
      queue_and_send(fd, rp);
      continue;
    }
    string key = (i < channelKeys.size()) ? channelKeys[i] : "";
    IRCChannel ircChannel;
    if (channels.find(channelName) != channels.end()) {
      ircChannel = channels[channelName];
    } else {
      ircChannel.setName(channelName);
      ircChannel.setCreatorNick(jClient.getNick());
      jClient.addChannel(channelName);
    }
    string joinRequest = genJoinReply(jClient, channelName);
    ChannelMode result = ircChannel.addUser(jClient.getNick(),USER_ONLY,key);
    if (result == ADD_USER_OK) {
      channels[channelName] = ircChannel;
      // :n01!~user1@lenovo-i5 JOIN :#test
      queue_and_send(jClient.getFd(), joinRequest); // ack join command
      // :ngircd.none.net 332 n02 #test :Channel usage # RPL_TOPIC
      string topic = genTopicReply(server_name, jClient.getNick(), ircChannel);
      queue_and_send(jClient.getFd(), topic);
      // :ngircd.none.net 333 n02 #test n01 1770644364 # Undef in RFC2812
      string timestamp = genCreationTimeReply(server_name, jClient.getNick(), ircChannel);
      queue_and_send(jClient.getFd(), timestamp);
      PairUserMapIterators pIts = ircChannel.getUsersIterators();
      for (UserMapIterator kvIt = pIts.first; kvIt != pIts.second; ++kvIt) { // scan all members of the channel
        string mNick = kvIt->first;
        if (nicks.find(mNick) == nicks.end()) continue;
        int mFD = nicks[mNick];
        if (clients.find(mFD) == clients.end()) continue;
        if (mFD != jClient.getFd()) { // broadcast join request except to the requestor
          queue_and_send(mFD, joinRequest); 
        }
        // send members of the channel to the requestor
        UserMode mUserMode = kvIt->second; // member user mode
        //:ngircd.none.net 353 n003 = #test :n003 n002 @n001
        string member = genMemberReply(server_name, jClient.getNick(), channelName, mUserMode, mNick);
        queue_and_send(jClient.getFd(), member);
      } // scan all members of the channel
      // :ngircd.none.net 366 n003 #test :End of NAMES list
      string endList = genEndList(server_name, jClient.getNick(), channelName);
      queue_and_send(jClient.getFd(), endList);
    } else if (result == INVITE_ONLY) {
      // :ngircd.none.net 473 japo #test :Cannot join channel (+i) -- Invited users only
      std::ostringstream buf;
      buf << server_name << " 473 " << jClient.getNick() << ' ' << channelName
        << " :Cannot join channel (+i) -- Invited users only\r\n";
      queue_and_send(jClient.getFd(), buf.str());
    } else if (result == KEY) {
      // :ngircd.none.net 475 japo #test :Cannot join channel (+k) -- Wrong channel key
      std::ostringstream buf;;
      buf << server_name << " 475 " << jClient.getNick() << ' ' << channelName
        << " :Cannot join channel (+k) -- Wrong channel key\r\n";
      queue_and_send(jClient.getFd(), buf.str()); 
    } else if (result == USER_LIMIT) {
      // :ngircd.none.net 471 japo #test :Cannot join channel (+l) -- Channel is full, try later
      std::ostringstream buf;;
      buf << server_name << " 471 " << jClient.getNick() << ' ' << channelName
        << " :Cannot join channel (+l) -- Channel is full, try later\r\n";
      queue_and_send(jClient.getFd(), buf.str());         
    }
  } // iterate over all requested channels
}

  

