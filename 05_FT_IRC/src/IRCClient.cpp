/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:45:05 by user1             #+#    #+#             */
/*   Updated: 2026/02/04 10:09:35 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <sstream>
#include <stdexcept>
#include <string>
#include "IRCClient.hpp"
#include "IRCMessage.hpp"
#include "utils.hpp"

IRCClient::IRCClient() : fd(-1) {}
IRCClient::IRCClient(int fd) : fd(fd) { 
  if (fd < 0) throw std::invalid_argument("invalid file descriptor");
}
IRCClient::IRCClient(const IRCClient &other):
    fd(other.fd), 
    nick(other.nick), 
    username(other.username), 
    fullname(other.fullname),
    channelNames(other.channelNames), 
    flags(other.flags) {}

IRCClient &IRCClient::operator=(const IRCClient &other) {
  if (this != &other) {
    this->nick = other.nick;
    this->username = other.username;
    this->fullname = other.fullname;
    this->fd = other.fd;
    this->channelNames = other.channelNames;
    this->flags = other.flags;
  }
  return *this;
}

IRCClient::~IRCClient() {
  nick.clear();
  username.clear();
  fullname.clear();
  fd = -1;
  channelNames.clear();
  flags.clear();
}

const std::string& IRCClient::getNick() const { return nick; }

bool IRCClient::setNick(const std::string& nick) {
  if (!isValidNick(nick)) return false;
  this->nick = nick;
  return true;
}

bool IRCClient::isValidNick(const std::string &nick) {
	if (nick.empty() || nick.length() > MAX_NICK_LENGTH) return false;

	if (!ft_isLetter(nick.at(0)) && !ft_isSpecial(nick.at(0))) return false;

	std::string::const_iterator it = nick.begin();
	for (++it; it != nick.end(); ++it) {
		if (ft_isLetter(*it)) continue;
		if (ft_isDigit(*it)) continue;
		if (ft_isSpecial(*it)) continue;
		if (*it == '-') continue;
		return false;
	}
	return true;
}
const std::string& IRCClient::getUsername() const { return username; }

bool IRCClient::setUsername(const std::string& username) {
  if (!isValidUsername(username)) return false;
  this->username = username;
  return true;
}

bool IRCClient::isValidUsername(const std::string &username) {
  if (username.empty() || username.length() >= MAX_MESSAGE_LENGTH)
    return false;
  std::string::const_iterator it;
  for (it = username.begin(); it != username.end(); ++it) {
      if ((*it & 0x80) || *it == '\0' || *it == '\r' || *it == '\n'
        || *it == '\f' || *it == '\t' || *it == '\v' || *it == ' ')
        return false;
    }
  return true;
}

const std::string& IRCClient::getFullname() const { return fullname; }
bool IRCClient::setFullname(const std::string& fullname) {
  if (!isValidFullname(fullname)) return false;
  this->fullname = fullname;
  return true;
}

bool IRCClient::isValidFullname(const std::string &fullname) {
  if (fullname.empty() || fullname.length() >= MAX_MESSAGE_LENGTH)
    return false;
  std::string::const_iterator it;
  for (it = fullname.begin(); it != fullname.end(); ++it) {
      if (*it == '\0') return false;
    }
  return true;  
}

int IRCClient::getFd() const { return fd; }

bool IRCClient::setFd(int fd) {
  if (fd < 0) return false;
  this->fd = fd;
  return true;
}

bool IRCClient::checkChannel(const std::string& channelName) const {
  return channelNames.count(channelName) != 0;
}

bool IRCClient::addChannel(const std::string& channelName) {
  return channelNames.insert(channelName).second;
}

bool IRCClient::delChannel(const std::string& channelName) {
  return channelNames.erase(channelName) != 0;
}

void IRCClient::clearChannels() {
  channelNames.clear();
}

pairIterators IRCClient::getChannelIterators() const {
  return pairIterators(
    channelNames.begin(), channelNames.end());
}

bool IRCClient::checkFlag(const FtIRCFlag& f) const {
  return flags.count(f) != 0;
}

bool IRCClient::setFlag(const FtIRCFlag& f) {
  if (f == PASS_FLAG)
    return flags.insert(f).second;
  if (!checkFlag(PASS_FLAG))
    return false;
  if (f == USER_FLAG && checkFlag(SERVICE_FLAG))
    return false;
  if (f == SERVICE_FLAG && checkFlag(USER_FLAG))
    return false;
  if (f == OPERATOR_FLAG && !checkFlag(USER_FLAG))
    return false;
  if (f == REGISTERED_FLAG) {
    if (!checkFlag(USER_FLAG) || !checkFlag(SERVICE_FLAG))
      return false;
  }
  return flags.insert(f).second;
}

bool IRCClient::unsetFlag(const FtIRCFlag& f) {
  return flags.erase(f) != 0;
}

void IRCClient::clearFlags() {
  flags.clear();
}

const std::string FtIRCFlagToString(FtIRCFlag flag)
{
    switch (flag) {
        case PASS_FLAG:       return "PASS_FLAG";
        case NICK_FLAG:       return "NICK_FLAG";
        case USER_FLAG:       return "USER_FLAG";
        case SERVICE_FLAG:    return "SERVICE_FLAG";
        case OPERATOR_FLAG:   return "OPERATOR_FLAG";
        case REGISTERED_FLAG: return "REGISTERED_FLAG";
        default:
          std::ostringstream oss;
          oss << "UNKNOWN_FLAG(" << flag << ")";
          return oss.str();
    }
}

std::string IRCClient::toString() const {
  std::ostringstream buf;
  buf << "fd=" << fd 
  << ", nick=\"" << nick 
  << "\", username=\"" << username
  << "\", fullname=\"" << fullname
  << "\", channelNames=[";
  if (!channelNames.empty()) {
    for (setOfStringsIterator it = channelNames.begin(); 
      it != channelNames.end(); ++it) {
      if (it != channelNames.begin()) buf << ", ";
      buf << '"' << *it << '"';
    }
  }
  buf << "], flags={";
  if (!flags.empty()) {
    std::set<FtIRCFlag>::const_iterator it;
    for (it = flags.begin(); it != flags.end(); ++it) {
      if (it != flags.begin()) buf << ", ";
      buf << FtIRCFlagToString(*it);
    }
  }
  buf << "}";
  return buf.str();
}

//Ibuffer

void IRCClient::addToIbuffer(const std::string & s)
{
  Ibuffer += s;
}

void IRCClient::addToIbuffer(const char * s, size_t n)
{
  Ibuffer.append(s, n);
}

void IRCClient::setIbuffer(const std::string & s)
{
  Ibuffer = s;
}

std::string & IRCClient::getIbuffer()
{
  return Ibuffer;
}


//Obuffer

void IRCClient::addToObuffer(const std::string & s)
{
  Obuffer += s;
}

void IRCClient::addToObuffer(const char * s, size_t n)
{
  Obuffer.append(s, n);
}

void IRCClient::setObuffer(const std::string & s)
{
  Obuffer = s;
}

std::string & IRCClient::getObuffer()
{
  return Obuffer;
}

std::string & IRCClient::getHost()
{
	return host;
}

void IRCClient::setHost(const std::string & s)
{
	host = s;
}


