/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCMessage.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:55:03 by user1             #+#    #+#             */
/*   Updated: 2026/02/09 21:18:03 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
#include <sstream>
#include <stdexcept>

#include "IRCCommand.hpp"
#include "IRCMessage.hpp"
#include "utils.hpp"

using std::invalid_argument;

/** Parameterized constructor
 */
IRCMessage::IRCMessage(const string prefix,
    const IRCCommand command,
    vector<string> params)
    : prefix(prefix)
    , command(command)
    , parameters(params)
{
}

IRCMessage::IRCMessage()
    : command(IRCCommand())
{
}

static void checkBasics(string& str)
{
    if (str.empty())
        throw invalid_argument("empty message");
    if (str.length() > MAX_MESSAGE_LENGTH)
        throw invalid_argument("message too large");
    if (str.find('\0') != std::string::npos)
        throw invalid_argument("message contains null char");
    string::size_type crlfPos = str.rfind("\r\n");
    if (crlfPos != string::npos) { // found crlf
        if (str.length() - crlfPos == 2) { // found crlf at end of string
            str.erase(crlfPos); // erase "\r\n" at the end
        } else { // found crlf not at the end of string
            throw invalid_argument("found more than one crlf");
        }
        if (str.find("\r\n") != string::npos) { // found crlf in the middle
            throw invalid_argument("found crlf in the middle");
        }
    }
}

/** Parse message string according to grammar from RFC2812,
  it might throw std::invalid_argument if not valid message.
  @param {std::string&} message received from a IRC client,
    the message can only have at most one sequence "\r\n" and at the end.
  @returns {IRCMessage} an IRCMessage object.
*/
IRCMessage IRCMessage::parse(string& str)
{
    checkBasics(str);
    string prefixStr;
    string cmdStr;
    string param;
    vector<string> params;
    string::const_iterator it = str.begin();
    int state = 1;
    while (state > 0) {
        switch (state) {
        case 1:
            if (*it == ' ')
                state = 1;
            else if (*it == ':')
                state = 2;
            else if (ft_isLetter(*it)) {
                cmdStr.append(1, *it);
                state = 4;
            } else if (ft_isDigit(*it)) {
                cmdStr.append(1, *it);
                state = 5;
            } else
                state = -1;
            break; // state == 1
        case 2:
            if (*it == ' ')
                state = 3;
            else if (it == str.end())
                state = -1;
            else
                prefixStr.append(1, *it);
            break; // state == 2
        case 3:
            if (*it == ' ')
                state = 3;
            else if (ft_isLetter(*it)) {
                cmdStr.append(1, *it);
                state = 4;
            } else if (ft_isDigit(*it)) {
                cmdStr.append(1, *it);
                state = 5;
            } else
                state = -1;
            break; // state == 3
        case 4:
            if (ft_isLetter(*it))
                cmdStr.append(1, *it);
            else if (*it == ' ') {
                param.clear();
                state = 6;
            } else if (it == str.end())
                state = 0;
            else
                state = -1;
            break; // state == 4
        case 5:
            if (ft_isDigit(*it))
                cmdStr.append(1, *it);
            else if (*it == ' ') {
                param.clear();
                state = 6;
            } else if (it == str.end())
                state = 0;
            else
                state = -1;
            break; // state == 5
        case 6:
            if (*it == ' ')
                state = 6;
            else if (*it == ':') {
                param.clear();
                state = 8;
            } else if (it == str.end()) {
                params.push_back(param);
                state = 0;
            } else {
                param.append(1, *it);
                state = 7;
            }
            break; // state == 6
        case 7:
            if (it == str.end()) {
                params.push_back(param);
                state = 0;
            } else if (*it == ' ') {
                params.push_back(param);
                param.clear();
                state = 6;
            } else
                param.append(1, *it);
            break; // state == 7
        case 8:
            if (it == str.end()) {
                params.push_back(param);
                state = 0;
            } else
                param.append(1, *it);
        }
        ++it;
    }
    if (state < 0)
        throw invalid_argument("invalid syntax");
    IRCCommand cmd = stringToIRCCommand(cmdStr);
    if (cmd == UNDEFINED)
        throw invalid_argument("unknown command");
    return IRCMessage(prefixStr, cmd, params);
}

IRCMessage::~IRCMessage() { }

IRCMessage::IRCMessage(const IRCMessage& other)
{
    this->prefix = other.prefix;
    this->command = other.command;
    this->parameters = other.parameters;
}

IRCMessage& IRCMessage::operator=(const IRCMessage& other)
{
    if (this == &other)
        return *this;
    this->prefix = other.prefix;
    this->command = other.command;
    this->parameters = other.parameters;
    return *this;
}

const string& IRCMessage::getPrefix() const
{
    return prefix;
}

vectorIteratorPairType IRCMessage::getParameters() const
{
    return vectorIteratorPairType(
        parameters.begin(), parameters.end());
}

vector<string>::size_type IRCMessage::getParametersSize() const
{
    return parameters.size();
}

IRCCommand IRCMessage::getCommand() const
{
    return command;
}

string IRCMessage::toString() const
{
    std::ostringstream buf;
    buf << "prefix=\"" << prefix
        << "\", command=" << IRCCommandtoString(command)
        << ", parameters=[";
    vectorIteratorPairType pIters = getParameters();
    vector<string>::const_iterator it;
    for (it = pIters.first; it != pIters.second; ++it) {
        if (it != pIters.first)
            buf << ", ";
        buf << '"' << *it << '"';
    }
    buf << "]";
    return buf.str();
}

const string& IRCMessage::getParam(size_t n) const
{
    if (n >= parameters.size())
        throw std::out_of_range("invalid index");
    return parameters[n];
}

const string IRCMessage::ircMessage() const
{
    std::ostringstream oss;
    if (prefix.empty())
        oss << ':' << prefix << ' ';
    oss << IRCCommandtoString(command);
    if (parameters.size() >= 1) {
        for (size_t i = 0; i < parameters.size() - 1; ++i) {
            if (i != 0)
                oss << ' ';
            oss << parameters[i];
        }
    }
    if (parameters.size() != 0)
        oss << " :" << parameters.back();
    return oss.str();
}

// for privmsg
const std::vector<std::string>& IRCMessage::getParamsVector() const
{
    return (parameters);
}
