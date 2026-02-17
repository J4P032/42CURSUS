/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2026/02/16 10:25:36 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <sstream>
#include <stdexcept>
#include <string>
#include "IRCClient.hpp"
#include "IRCMessage.hpp"
#include "utils.hpp"


IRCClient::IRCClient() : fd(-1), last_activity(std::time(NULL)), server_ping_sent(false) {}
IRCClient::IRCClient(int fd) : fd(fd), last_activity(std::time(NULL)), server_ping_sent(false) { 
  if (fd < 0) throw std::invalid_argument("invalid file descriptor");
}
IRCClient::IRCClient(const IRCClient &other):
    fd(other.fd), 
    nick(other.nick), 
    username(other.username), 
    fullname(other.fullname),
    host(other.host),
    channelNames(other.channelNames), 
    flags(other.flags),
    Ibuffer(other.Ibuffer),
    Obuffer(other.Obuffer),
    last_activity(other.last_activity),
    server_ping_sent(other.server_ping_sent){}

IRCClient &IRCClient::operator=(const IRCClient &other) {
  if (this != &other) {
    this->nick = other.nick;
    this->username = other.username;
    this->fullname = other.fullname;
    this->host = other.host;
    this->fd = other.fd;
    this->channelNames = other.channelNames;
    this->flags = other.flags;
    Ibuffer = other.Ibuffer;
    Obuffer = other.Obuffer;
    this->last_activity = other.last_activity;
    server_ping_sent = other.server_ping_sent;
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
  ft_toLower(this->nick);
  return true;
}

bool IRCClient::isValidNick(const std::string &nick) {
	if (nick.empty() || nick.length() > MAX_NICK_LENGTH) return false;

	if (!ft_isLetter(nick[0]) && !ft_isSpecial(nick[0])) return false;

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
  if (!isValidFullname(fullname)) {
		return false;
  }
  this->fullname = fullname;
  return true;
}

bool IRCClient::isValidFullname(const std::string &fullname) {
  if (fullname.empty() || fullname.length() >= MAX_MESSAGE_LENGTH) {
    return false;
  }
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
  string lcChannelName = channelName;
  ft_toLower(lcChannelName);
  return channelNames.find(lcChannelName) != channelNames.end();
}

bool IRCClient::addChannel(const std::string& channelName) {
  string lcChannelName = channelName;
  ft_toLower(lcChannelName);
  return channelNames.insert(lcChannelName).second;
}

bool IRCClient::delChannel(const std::string& channelName) {
  string lcChannelName = channelName;
  ft_toLower(lcChannelName);
  return channelNames.erase(lcChannelName) != 0;
}

void IRCClient::clearChannels() {
  channelNames.clear();
}

pairIterators IRCClient::getChannelIterators() const {
  return pairIterators(
    channelNames.begin(), channelNames.end());
}

bool IRCClient::checkFlag(const FtIRCFlag& f) const {
  return flags.find(f) != flags.end();
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
  << "\", host=\"" << host
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

const std::string& IRCClient::getHost() const
{
	return host;
}

void IRCClient::setHost(const std::string & s)
{
	host = s;
}

time_t  IRCClient::getLastActivity(void) const {
  return (last_activity);
}

void    IRCClient::updateLastActivity(void){
  last_activity = std::time(NULL);
}

bool    IRCClient::get_server_ping_sent(void){
  return (server_ping_sent);
}
  
void    IRCClient::set_server_ping_sent(void){
  server_ping_sent = true;
}

const std::set<std::string>& IRCClient::getChannelNames() const {
  return channelNames;
}

