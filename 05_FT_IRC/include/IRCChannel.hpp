/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCChannel.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:10:45 by user1             #+#    #+#             */
/*   Updated: 2026/02/10 16:05:37 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCHANNEL_HPP
#define IRCCHANNEL_HPP
#include "IRCMessage.hpp"
#include <cstddef>
#include <string>
#include <set>
#include <map>

using std::map;
using std::string;
using std::set;
using std::pair;

typedef enum {
  ADD_USER_OK,  // Invalid in Mode only used as a return value in addUser
  INVITE_ONLY,
  TOPIC,
  KEY,
  USER_LIMIT  // MODES in subject doc
  // ANONYMOUS,
  // MODERATED,
  // NO_EXTERNAL_USERS,
  // QUIET,
  // PRIVATE,
  // SECRET,
  // BAN,
  // BAN_EXCEPTION,
} ChannelMode;
typedef set<ChannelMode>::const_iterator ChannelModeIterator;
typedef pair<ChannelModeIterator, ChannelModeIterator> 
  PairChannelModesIterators;

/** @returns a string describing the ChannelMode */
const string& channelModeToString(ChannelMode chMode);


typedef enum {
  UNDEF,
  USER_ONLY,
  CHANNEL_OPERATOR
} UserMode;
typedef map<string,UserMode>::const_iterator UserMapIterator;
typedef pair<UserMapIterator,UserMapIterator> PairUserMapIterators;

/** @returns a string describing the UserMode */
const string& userModeToString(UserMode uMode);


class IRCChannel {
public:
const static unsigned MAX_NAME_LENGTH = 50;

  IRCChannel();
	IRCChannel(const string& name);
  IRCChannel(const IRCChannel& other);
  IRCChannel& operator=(const IRCChannel& other);
  virtual ~IRCChannel();

  /** Checks if the name is valid according to RFC2811 */
  static bool isValidName(const string& channelName);
  
  const string& getName() const;
  bool setName(const string& name);
  
  bool operator==(const IRCChannel& rhs) const;
  bool operator<(const IRCChannel& rhs) const;
  bool operator>(const IRCChannel& rhs) const;
  bool operator<=(const IRCChannel& rhs) const;
  bool operator>=(const IRCChannel& rhs) const;

  /** Check user belongs to this Channel */
  bool checkUser(const string& nick) const;
  
  /** Add/Del user to this channel 
  @returns ADD_USER_OK if the operation was performed 
  If channel is key protected and supplied userKey != channelKey 
    returns KEY
  
  If channel has a limited number of users and the limit is reached
    returns USER_LIMIT

  If channel is invite only and user is not in the inveted list
    return INVITE_ONLY 
  */
  ChannelMode addUser(const string& nick, UserMode userMode = USER_ONLY, const string& userKey = "");
  bool delUser(const string& nick);
  
  /** Delete all users from this channel, this means this 
  channel should cease to exist */
  void clearUsers();

  /** Set a UserMode to a particular user in this channel, 
  if this is the first user added it is automatically made 
  CHANNEL_OPERATOR */
  bool setUserMode(const string& nick, UserMode userMode);

  /** @returns the UserMode an user is set in this Channel.
  If the user does not belong to it returns UNDEF */
  UserMode getUserMode(const string& nick) const;
  
  /** @returns a pair of UserMapIterator.
  UserMapIterator points to a pair with first==nick and second its UserMode
  Usage:
  PairUserMapIterators pairIterators = getUsersIterators();
  for (UserMapIterator kvIt = pairIterators.first;
        kvIt != pairIterators.second; ++kvIt) {
    string nick = kvIt->first;
    UserMode um = kvIt->second;
    ...
  }
  */
	PairUserMapIterators getUsersIterators() const;

  /** @returns the number of users subscribed to this channel */
  size_t getNumberOfUsers() const;
  
  /** @returns the key (password) to access this Channel.
  Only active if this channel has the ChannelMode KEY set */
  const string& getKey() const;

  /** Sets the key (password) to access this Channel.
  Only active if this channel has the ChannelMode KEY set */
  void setKey(const string& key);

  /** Checks this channel has a particular mode set */
  bool checkChannelMode(const ChannelMode chMode) const;

  /** Adds a particular mode to this channel */
  bool setChannelMode(const ChannelMode chMode);

  /** Delete a particular mode from this channel */
  bool unsetChannelMode(const ChannelMode chMode);

  /** @returns a pair of channelModeIterator.
  A channelModeIterator iterates over a set of modes of this channel
  the usage is:
  channelModesIterators pair = getChannelModesIterators();
  for (channelModeIterator it = pair.first; it != pair.second; ++it) {
    ... // each *it is a ChannelMode 
  }
  */
  PairChannelModesIterators getChannelModesIterators() const;
  
  /** @returns the maximum number of users subscribed to this channel.
  Only active if this channel has USER_LIMIT mode set */
  size_t getUserLimit() const;

  /** Sets the maximum number of users subscribed to this channel.
  Only active if this channel has USER_LIMIT mode set */
  void setUserLimit(size_t userLimit);

  /** @returns {const string&} current topic for the channel */
  const string& getTopic() const;
  
  /** Sets a new topic to the channel.
  If current channel is moderated (mode TOPIC set) the user
  requesting the change must be a CHANNEL_OPERATOR
  @returns (bool) true if all conditions met  */
  bool setTopic(const string& user, const string& newTopic); 

  /** Generates a text view of the object
  * @returns {std::string} with the contents of the object */
  string toString() const;

  /** Add an invited nick, @returns false if nick already invited */
  bool addInvitedNick(const string& nick);

  /** Check if a nick was invited */
  bool checkInvitedNick(const string& nick) const;

  /** Del nick from invited list, @returns false if nick was invited */
  bool delInvitedNick(const string& nick);

  /** Del all nicks from invited list */
  void delAllInvitedNicks();

private:
  string name;     // channel name
	map<string, UserMode> nicks; // nick => UserMode
  string key;                       // password to join the channel
  set<ChannelMode> channelModes;
  size_t userLimit;                 // max number of clients
  string topic;                     // current channel topic
  set<string> invitedNicks;         // nicks invited
};
#endif
