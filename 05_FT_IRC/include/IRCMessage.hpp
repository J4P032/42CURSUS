/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:44:00 by user1             #+#    #+#             */
/*   Updated: 2026/02/03 17:22:50 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCMESSAGE_HPP
#define IRCMESSAGE_HPP

#include <string>
#include <vector>
#include "IRCCommand.hpp"

#define MAX_MESSAGE_LENGTH 512
#define MAX_NICK_LENGTH 9

using std::string;
using std::vector;
using std::pair;

typedef pair<vector<string>::const_iterator, vector<string>::const_iterator> vectorIteratorPairType;
class IRCMessage {
public:
	IRCMessage();
  IRCMessage(const string prefix, const IRCCommand command, vector<string> params);
  static IRCMessage parse(string& str);
  virtual ~IRCMessage();
  IRCMessage(const IRCMessage& other);
  IRCMessage& operator=(const IRCMessage& other);
  const string& getPrefix() const;
  vectorIteratorPairType getParameters() const;
  vector<string>::size_type getParametersSize() const;
  IRCCommand getCommand() const;
  string toString() const;
private:
  string prefix;
  IRCCommand command;
  vector<string> parameters;
};
#endif
