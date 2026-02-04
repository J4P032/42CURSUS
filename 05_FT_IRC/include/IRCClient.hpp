/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:36:20 by user1             #+#    #+#             */
/*   Updated: 2026/02/03 19:59:15 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCLIENT_HPP
#define IRCCLIENT_HPP
#include <set>
#include <string>
#include "utils.hpp"

typedef enum {
  PASS_FLAG,        // after PASS command
  NICK_FLAG,        // after NICK command
  USER_FLAG,        // after USER command
  SERVICE_FLAG,     // after SERVICE command
  OPERATOR_FLAG,    // after OPERATOR command
  REGISTERED_FLAG,  // after PASS, NICK, (USER || SERVICE) commands
} FtIRCFlag;

const std::string FtIRCFlagToString(FtIRCFlag flag);

class IRCClient {
public:
  IRCClient();
  IRCClient(int fd);
  IRCClient(const IRCClient& other);
  IRCClient& operator=(const IRCClient& other);
  virtual ~IRCClient();
  
  /** Getter for nick name*/
  const std::string& getNick() const;
  bool setNick(const std::string& nick);
  static bool isValidNick(const std::string& nick);

  /** Getter for username*/
  const std::string& getUsername() const;
  bool setUsername(const std::string& username);
  static bool isValidUsername(const std::string& username);
	
  const std::string& getFullname() const;
  bool setFullname(const std::string& fullname);
  static bool isValidFullname(const std::string& fullname);

  /** Getter for file descriptor associated to this client*/
  int getFd() const;
  bool setFd(int fd);


  /** Verifies if the client belongs to a channel given its name*/
  bool checkChannel(const std::string& channelName) const;
  bool addChannel(const std::string& channelName);
  bool delChannel(const std::string& channelName);
  void clearChannels();

  /** Getter for const iterators (begin, end) of the set of joined channels*/
  pairIterators getChannelIterators() const;

  /** Verifies whether a flag is set for this client*/
  bool checkFlag(const FtIRCFlag& f) const;
  bool setFlag(const FtIRCFlag& f);
  bool unsetFlag(const FtIRCFlag& f);
  void clearFlags();
  
  /** Generates a text view of the object*/
  std::string toString() const;

	/** Set & Get host Obuffer */
  void addToIbuffer(const std::string & s);
  void addToIbuffer(const char * s, size_t n);
  void setIbuffer(const std::string & s);
  std::string & getIbuffer();

	/** Set & Get host Obuffer */
  void addToObuffer(const std::string & s);
  void addToObuffer(const char * s, size_t n);
  void setObuffer(const std::string & s);
  std::string & getObuffer();

	/** Set & Get host*/
	std::string & getHost();
	void setHost(const std::string & s);

private:
  int fd;
  std::string nick;
  std::string username;
  std::string fullname;
  std::string host;
  std::set<std::string> channelNames;
  std::set<FtIRCFlag> flags;
  std::string Ibuffer;
  std::string Obuffer;
};

#endif
