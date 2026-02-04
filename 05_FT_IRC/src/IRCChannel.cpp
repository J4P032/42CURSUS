/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCChannel.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:12:14 by user1             #+#    #+#             */
/*   Updated: 2026/02/02 16:03:11 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCChannel.hpp"
#include "utils.hpp"
#include <sstream>
#include <utility>

IRCChannel::IRCChannel(): name("undefined") {}

IRCChannel::IRCChannel(const std::string& name): name(name) {}

IRCChannel::IRCChannel(const IRCChannel& other):
  name(other.name), nicks(other.nicks) {}

  IRCChannel& IRCChannel::operator=(const IRCChannel& other) {
  if (this != &other) {
    name = other.name;
    nicks = other.nicks;
  }
  return *this;
}
    
IRCChannel::~IRCChannel() {}

const std::string& IRCChannel::getName() const {
  return name;
}

bool IRCChannel::setName(const std::string& name) {
  this->name = name;
  return true;
}

bool IRCChannel::checkUser(const std::string& user) const {
  return nicks.count(user) != 0;
}

bool IRCChannel::addUser(const std::string& nick) {
  return nicks.insert(nick).second;
}

bool IRCChannel::delUser(const std::string& nick) {
  return nicks.erase(nick) != 0;
}

void IRCChannel::clearUsers() {
  nicks.clear();
}

pairIterators IRCChannel::getChannelIterators() const {
  return pairIterators(nicks.begin(), nicks.end());
}

void IRCChannel::sendMessageThrough(IRCMessage& msg) const {
  // TODO
  (void)msg;
}

  /** Generates a text view of the object
  * @returns {std::string} with the contents of the object */
std::string IRCChannel::toString() const {
  std::ostringstream buf;
  buf << "name=\"" << name << "\", nicks=[";
  for (setOfStringsIterator it = nicks.begin(); it != nicks.end(); ++it) {
    if (it != nicks.begin()) buf << ", ";
    buf << '"' << *it << '"';
  }
  buf << "]";
  return buf.str();
}