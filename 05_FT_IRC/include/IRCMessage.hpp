/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:44:00 by user1             #+#    #+#             */
/*   Updated: 2026/02/09 21:16:45 by jrollon-         ###   ########.fr       */
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
  /** Cannonical Orthodox Methods */
	IRCMessage();
  IRCMessage(const string prefix, const IRCCommand command, vector<string> params);
  virtual ~IRCMessage();
  IRCMessage(const IRCMessage& other);
  IRCMessage& operator=(const IRCMessage& other);
  
  /** Convert a raw message to an IRCMessage object. 
  If message cannot be parsed or the command part is not recognized
  throws std::invalid_argument exception.*/
  static IRCMessage parse(string& str);
  
  /** @returns prefix part of the IRC message */
  const string& getPrefix() const;

  /** @returns a pair of vector<string> iterators corresponding
  to begin() and end(). */
  vectorIteratorPairType getParameters() const;

  /** @returns the number of parameters found. */
  vector<string>::size_type getParametersSize() const;

  /** @returns the n-th parameter of the list.
  Throws std::out_of_range exception if the index is invalid */
  const string& getParam(size_t n) const;
  
  //for privmsg
  const std::vector<std::string>& getParamsVector() const;

  /** @returns the corresponding IRCCommand enum from the message */
  IRCCommand getCommand() const;

  /** @returns a IRC protocol message from its components */
  const string ircMessage() const;

  /** @returns a displayable string with all object fields, use for debugging */
  string toString() const;
private:
  string prefix;
  IRCCommand command;
  vector<string> parameters;
};
#endif
