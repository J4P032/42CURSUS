/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCChannel.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:12:14 by user1             #+#    #+#             */
/*   Updated: 2026/02/11 15:22:03 by mvassall         ###   ########.fr       */
/*   Updated: 2026/02/11 12:29:10 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCChannel.hpp"
#include "IRCServ.hpp"
#include "utils.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>

IRCChannel::IRCChannel()
    : name("INVALID_NAME")
    , userLimit(0)
{
    creationTime = std::time(NULL);
}

/** the channel name is stored in lower case */
IRCChannel::IRCChannel(const string& name, const string& creatorNick)
{
    if (!isValidName(name))
        throw std::invalid_argument("invalid channel name");
    this->name = name;
    ft_toLower(this->name);
    userLimit = 0;
    creationTime = std::time(NULL);
    string lcCreatorNick = creatorNick;
    ft_toLower(lcCreatorNick);
    this->creatorNick = lcCreatorNick;
}

IRCChannel::IRCChannel(const IRCChannel& other)
    : name(other.name)
    , nicks(other.nicks)
    , key(other.key)
    , channelModes(other.channelModes)
    , userLimit(other.userLimit)
    , topic(other.topic)
    , invitedNicks(other.invitedNicks)
    , creationTime(other.creationTime)
    , creatorNick(other.creatorNick)
{
}

IRCChannel& IRCChannel::operator=(const IRCChannel& other)
{
    if (this != &other) {
        name = other.name;
        nicks = other.nicks;
        key = other.key;
        channelModes = other.channelModes;
        userLimit = other.userLimit;
        topic = other.topic;
        invitedNicks = other.invitedNicks;
        creationTime = other.creationTime;
        creatorNick = other.creatorNick;
    }
    return *this;
}

IRCChannel::~IRCChannel() { }

bool IRCChannel::isValidName(const std::string& name)
{
    // maxlength 50 chars
    if (name.length() > MAX_NAME_LENGTH)
        return false;
    // must start with any of "#&+", safe channels starting with '!'
    // are not implemented
    static const std::string VALID_PREFIX = "#&+!";
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

bool IRCChannel::operator==(const IRCChannel& rhs) const
{
    return name == rhs.name;
}

bool IRCChannel::operator<(const IRCChannel& rhs) const
{
    return name < rhs.name;
}

bool IRCChannel::operator>(const IRCChannel& rhs) const
{
    return rhs.name < name;
}

bool IRCChannel::operator<=(const IRCChannel& rhs) const
{
    return !(name > rhs.name);
}

bool IRCChannel::operator>=(const IRCChannel& rhs) const
{
    return !(name < rhs.name);
}

const string& IRCChannel::getName() const
{
    return name;
}

bool IRCChannel::setName(const std::string& name)
{
    if (!isValidName(name))
        return false;
    std::string aux = name;
    ft_toLower(aux);
    this->name = aux;
    return true;
}

bool IRCChannel::checkUser(const string& nick) const
{
    string lcNick = nick;
    ft_toLower(lcNick);
    return nicks.find(lcNick) != nicks.end();
}

ChannelMode IRCChannel::addUser(
    const string& nick,
    UserMode userMode,
    const string& userKey)
{
    string lcNick = nick;
    ft_toLower(lcNick);
    if (checkUser(lcNick))
        return ADD_USER_OK;
    if (nicks.empty()) {
        nicks[lcNick] = CHANNEL_OPERATOR;
        return ADD_USER_OK;
    }
    if (checkChannelMode(USER_LIMIT) && nicks.size() >= userLimit)
        return USER_LIMIT;
    if (checkChannelMode(INVITE_ONLY) && !checkInvitedNick(lcNick)) {
        return INVITE_ONLY;
    }
    if (checkChannelMode(KEY) && (userKey != key)) {
        return KEY;
    }
    nicks[lcNick] = userMode;
    if (checkInvitedNick(lcNick)) delInvitedNick(lcNick);
    return ADD_USER_OK;
}

bool IRCChannel::delUser(const string& nick)
{
    string lcNick = nick;
    ft_toLower(lcNick);
    return nicks.erase(lcNick) != 0;
}

void IRCChannel::clearUsers()
{
    nicks.clear();
}

bool IRCChannel::setUserMode(const string& nick, UserMode userMode)
{
    if (!checkUser(nick))
        return false;
    string lcNick = nick;
    ft_toLower(lcNick);
    nicks[lcNick] = userMode;
    return true;
}

UserMode IRCChannel::getUserMode(const string& nick) const
{
    string lcNick = nick;
    ft_toLower(lcNick);
    map<string, UserMode>::const_iterator it = nicks.find(lcNick);
    if (it == nicks.end())
        return UNDEF;
    return it->second;
}

PairUserMapIterators IRCChannel::getUsersIterators() const
{
    return PairUserMapIterators(nicks.begin(), nicks.end());
}

size_t IRCChannel::getNumberOfUsers() const
{
    return nicks.size();
}

const string& IRCChannel::getKey() const
{
    return this->key;
}

void IRCChannel::setKey(const string& key)
{
    this->key = key;
}

bool IRCChannel::checkChannelMode(const ChannelMode chMode) const
{
    if (chMode == ADD_USER_OK)
        return false;
    return channelModes.find(chMode) != channelModes.end();
}

bool IRCChannel::setChannelMode(const ChannelMode chMode)
{
    if (chMode == ADD_USER_OK)
        return false;
    return channelModes.insert(chMode).second;
}

bool IRCChannel::unsetChannelMode(const ChannelMode chMode)
{
    if (chMode == ADD_USER_OK)
        return false;
    return channelModes.erase(chMode) != 0;
}

const string& IRCChannel::getTopic() const
{
    return topic;
}

bool IRCChannel::setTopic(const string& nick, const string& newTopic)
{
    string lcNick = nick;
    ft_toLower(lcNick);
    if ((!checkChannelMode(TOPIC))
        || (checkUser(lcNick) && nicks[lcNick] == CHANNEL_OPERATOR)) {
        topic = newTopic;
        return true;
    }
    return false;
}

PairChannelModesIterators IRCChannel::getChannelModesIterators() const
{
    return PairChannelModesIterators(
        channelModes.begin(), channelModes.end());
}

size_t IRCChannel::getUserLimit() const
{
    return userLimit;
}

void IRCChannel::setUserLimit(size_t userLimit)
{
    this->userLimit = userLimit;
}

/** Generates a text view of the object
 * @returns {std::string} with the contents of the object */
std::string IRCChannel::toString() const
{
    std::ostringstream buf;
    buf << "name=\"" << name << "\", nicks=[";
    for (map<string, UserMode>::const_iterator it = nicks.begin();
        it != nicks.end(); ++it) {
        if (it != nicks.begin())
            buf << ", ";
        buf << "('"
            << it->first << "', "
            << userModeToString(it->second) << ')';
    }
    buf << ']';
    buf << ", key=\"" << key << "\""
        << ", userLimit=" << userLimit
        << ", creationTime=" << creationTime
        << ", creatorNick=" << creatorNick
        << ", channelModes=[";
    for (set<ChannelMode>::const_iterator it = channelModes.begin();
        it != channelModes.end(); ++it) {
        if (it != channelModes.begin())
            buf << ", ";
        buf << channelModeToString(*it);
    }
    buf << ']';
    buf << ", invitedNicks=[";
    for (set<string>::const_iterator it = invitedNicks.begin();
        it != invitedNicks.end(); ++it) {
        if (it != invitedNicks.begin())
            buf << ", ";
        buf << *it;
    }
    buf << ']';
    return buf.str();
}

const string& channelModeToString(ChannelMode chMode)
{
    static map<ChannelMode, string> m;
    if (m.empty()) {
        m[INVITE_ONLY] = "i";
        m[TOPIC] = "t";
        m[KEY] = "k";
        m[USER_LIMIT] = "l";
        m[INVITE_ONLY] = "i";
        m[TOPIC] = "t";
        m[KEY] = "k";
        m[USER_LIMIT] = "l";
    }
    return m[chMode];
}

const string& userModeToString(UserMode uMode)
{
    static map<UserMode, string> m;
    if (m.empty()) {
        m[UNDEF] = "UNDEF";
        m[USER_ONLY] = "USER_ONLY";
        m[CHANNEL_OPERATOR] = "CHANNEL_OPERATOR";
    }
    return m[uMode];
}

bool IRCChannel::addInvitedNick(const string& nick)
{
    string lcNick = nick;
    ft_toLower(lcNick);
    return invitedNicks.insert(lcNick).second;
}

bool IRCChannel::checkInvitedNick(const string& nick) const
{
    string lcNick = nick;
    ft_toLower(lcNick);
    return invitedNicks.find(lcNick) != invitedNicks.end();
}

bool IRCChannel::delInvitedNick(const string& nick)
{
    string lcNick = nick;
    ft_toLower(lcNick);
    return invitedNicks.erase(lcNick) > 0;
}

void IRCChannel::delAllInvitedNicks()
{
    invitedNicks.clear();
}

const set<ChannelMode>& IRCChannel::getChannelModes() const
{
    return channelModes;
}

const map<string, UserMode>& IRCChannel::getNicksMap() const
{
    return nicks;
}

const set<string>& IRCChannel::getInvitedNicks() const
{
    return invitedNicks;
}

size_t IRCChannel::getCreationTime() const
{
    return creationTime;
}

const string& IRCChannel::getCreatorNick() const
{
    return creatorNick;
}

void IRCChannel::setCreatorNick(const string& nick)
{
    string lcNick = nick;
    ft_toLower(lcNick);
    creatorNick = lcNick;
}

void partChannel(IRCServ& ircServer, IRCClient& client, IRCChannel& channel, const string& byeMsg)
{
    std::ostringstream buf;
    buf << ':' << client.getNick() << '!' << client.getUsername() << '@' << client.getHost()
        << " PART " << channel.getName() << " :"
        << (byeMsg.empty() ? "client leaving" : byeMsg)
        << "\r\n";
    const string reply = buf.str();
    std::map<const std::string, int> allNicks2Fd = ircServer.getNicks();
    for (map<string, UserMode>::const_iterator it = channel.getNicksMap().begin();
        it != channel.getNicksMap().end(); ++it) { // go thru all list members
        string mNick = it->first; // member nick
        if (allNicks2Fd.find(mNick) == allNicks2Fd.end())
            continue;
        int mFD = allNicks2Fd[mNick];
        if (ircServer.getClients().find(mFD) == ircServer.getClients().end())
            continue;
        ircServer.queue_and_send(mFD, reply);
    }
    channel.delUser(client.getNick());
    client.delChannel(channel.getName());
    if (channel.getNumberOfUsers() == 0) {
        ircServer.delEmptyChannel(channel.getName());
    }
}
