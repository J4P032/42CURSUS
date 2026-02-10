/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCChannel.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:12:14 by user1             #+#    #+#             */
/*   Updated: 2026/02/09 15:48:56 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCChannel.hpp"
#include "utils.hpp"
#include <sstream>
#include <stdexcept>

IRCChannel::IRCChannel(): name("invalid"), userLimit(0) {}

IRCChannel::IRCChannel(const std::string& name) {
  if (!isValidName(name))
    throw std::invalid_argument("invalid channel name");
  this->name = name;
  ft_toLower(this->name);
  userLimit = 0;
}

IRCChannel::IRCChannel(const IRCChannel& other):
  name(other.name),
  nicks(other.nicks),
  key(other.key),
  channelModes(other.channelModes),
  userLimit(other.userLimit) {}

  IRCChannel& IRCChannel::operator=(const IRCChannel& other) {
  if (this != &other) {
    name = other.name;
    nicks = other.nicks;
    key = other.key;
    channelModes = other.channelModes;
    userLimit = other.userLimit;
  }
  return *this;
}
    
IRCChannel::~IRCChannel() {}

bool IRCChannel::isValidName(const std::string &name) {
  // maxlength 50 chars
  if (name.length() > MAX_NAME_LENGTH) return false;
  // must start with any of "#&+", safe channels starting with '!'
  // are not implemented
  static const std::string VALID_PREFIX = "#&+";  
  if (VALID_PREFIX.find_first_of(name[0]) == std::string::npos)
    return false;
  // must not have any of chars " ,:\x07"
  static const std::string INVALID_CHARS = " ,:\x07";
  for (std::string::const_iterator it = INVALID_CHARS.begin();
      it != INVALID_CHARS.end(); ++it)
    if (name.find_first_of(*it) != std::string::npos)
      return false;
  return true;
}

const string& IRCChannel::getName() const {
  return name;
}

bool IRCChannel::setName(const std::string& name) {
  if (!isValidName(name))
    return false;
  this->name = name;
  ft_toLower(this->name);
  return true;
}

bool IRCChannel::checkUser(const string& nick) const {
  return nicks.count(nick) != 0;
}

bool IRCChannel::addUser(const string& nick, UserMode userMode) {
  if (nicks.count(nick) != 0)
    return false;
  nicks[nick] = nicks.empty()? CHANNEL_OPERATOR : userMode;
  return true;
}

bool IRCChannel::delUser(const string& nick) {
  return nicks.erase(nick) != 0;
}

void IRCChannel::clearUsers() {
  nicks.clear();
}

bool IRCChannel::setUserMode(const string& nick, UserMode userMode) {
  if (nicks.count(nick) == 0) return false;
  nicks[nick] = userMode;
  return true;
}

UserMode IRCChannel::getUserMode(const string& nick) const {
  if (nicks.count(nick) == 0) return UNDEF;
  return nicks.at(nick);
}

PairUserMapIterators IRCChannel::getUsersIterators() const {
  return PairUserMapIterators(nicks.begin(), nicks.end());
}

size_t IRCChannel::getNumberOfUsers() const {
  return nicks.size();
}

const string& IRCChannel::getKey() const {
  return this->key;
}

void IRCChannel::setKey(const string& key) {
  this->key = key;
}

bool IRCChannel::checkChannelMode(const ChannelMode chMode) const {
  return channelModes.count(chMode) != 0;
}

bool IRCChannel::setChannelMode(const ChannelMode chMode) {
  return channelModes.insert(chMode).second;
}

bool IRCChannel::unsetChannelMode(const ChannelMode chMode) {
  return channelModes.erase(chMode) != 0;
}

const string& IRCChannel::getTopic() const {
  return topic;
}

bool IRCChannel::setTopic(const string& nick, const string& newTopic) {
  if ((channelModes.count(TOPIC) == 0)
    || (nicks.count(nick) != 0 && nicks[nick] == CHANNEL_OPERATOR)) {
    topic = newTopic;
    return true;
  }
  return false;
} 

PairChannelModesIterators IRCChannel::getChannelModesIterators() const {
  return PairChannelModesIterators(
    channelModes.begin(), channelModes.end());
}

unsigned IRCChannel::getUserLimit() const {
  return userLimit;
}

void IRCChannel::setUserLimit(unsigned userLimit) {
  this->userLimit = userLimit;
}

  /** Generates a text view of the object
  * @returns {std::string} with the contents of the object */
std::string IRCChannel::toString() const {
  std::ostringstream buf;
  buf << "name=\"" << name << "\", nicks=[";
  for (map<string,UserMode>::const_iterator it = nicks.begin();
    it != nicks.end(); ++it) {
    if (it != nicks.begin()) buf << ", ";
    buf << "('" 
      << it->first << "', "
      << userModeToString(it->second) << ')';
  }
  buf << "]";
  buf << ", key=\"" << key << "\", userLimit=" << userLimit
    << ", channelModes=[";
  for (set<ChannelMode>::const_iterator it = channelModes.begin();
    it != channelModes.end(); ++it) {
    if (it != channelModes.begin()) buf << ", ";
    buf << channelModeToString(*it);    
  }
  buf << ']';
  return buf.str();
}

const string& channelModeToString(ChannelMode chMode) {
  static map<ChannelMode,string> m;
  if (m.empty()) {
    m[INVITE_ONLY] = "INVITE_ONLY";
    m[TOPIC] = "TOPIC";
    m[KEY] = "KEY";
    m[USER_LIMIT] = "USER_LIMIT";
  }
  return m[chMode];
}

const string& userModeToString(UserMode uMode) {
  static map<UserMode,string> m;
  if (m.empty()) {
    m[UNDEF] = "UNDEF";
    m[USER_ONLY] = "USER_ONLY";
    m[CHANNEL_OPERATOR] = "CHANNEL_OPERATOR";
  }
  return m[uMode];
}