/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCChannel.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:10:45 by user1             #+#    #+#             */
/*   Updated: 2026/02/03 11:57:17 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCHANNEL_HPP
#define IRCCHANNEL_HPP
#include "IRCMessage.hpp"
#include "utils.hpp"
#include <string>
#include <set>

class IRCChannel {
public:
  IRCChannel();
	IRCChannel(const std::string& name);
  IRCChannel(const IRCChannel& other);
  IRCChannel& operator=(const IRCChannel& other);
  virtual ~IRCChannel();


  const std::string& getName() const;
  bool setName(const std::string& name);
  bool checkUser(const std::string& channelName) const;
  bool addUser(const std::string& nick);
  bool delUser(const std::string& nick);
  void clearUsers();
	pairIterators getChannelIterators() const;
  
  void sendMessageThrough(IRCMessage& msg) const;

  /** Generates a text view of the object
  * @returns {std::string} with the contents of the object */
  std::string toString() const;
private:
  std::string name;
	std::set<std::string> nicks;
};
#endif
