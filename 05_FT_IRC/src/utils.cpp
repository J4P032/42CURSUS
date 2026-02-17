/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcoga2 <marcoga2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:22:07 by user1             #+#    #+#             */
/*   Updated: 2026/02/10 15:29:26 by marcoga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "IRCCommand.hpp"
#include <climits>
#include <cstring>
#include <limits>
#include <sstream>
#include <unistd.h>
#include <utility>
#include <vector>

bool ft_isLetter(char c) {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool ft_isDigit(char c) {
  return ('0' <= c && c <= '9');
}

// [ ] { } \ ^ _ ` |
bool ft_isSpecial(char c) {
  return (0x5B <= c && c <= 0x60) || (0x7B <= c && c <= 0x7D);
}

std::string ft_itoa(int n) {
  std::ostringstream os;
  os << n;
  return os.str();    
}

/** Parse a string to int value using re /' '*[-]d+/
* @param {const std::string} input
* @returns {std::pair<int,bool>} .second == false if conversion has failed
* .first the int value parsed
*/
std::pair<int, bool> ft_atoi(const std::string& str) {
  bool isNegative = false;
  int digitCount = 0;
  long l = 0;
  std::string::const_iterator it;
  for (it = str.begin(); it != str.end(); ++it) {
    if (*it == ' ') continue;
    if (ft_isDigit(*it)) {
      digitCount++;
      l = (l * 10) + (*it - '0');
      if (l > std::numeric_limits<int>::max())
        return std::pair<int, bool>(0,false);
      continue;
    }
    break;
  }
  if (digitCount == 0) return std::pair<int,bool>(0, false);
  if (isNegative) l *= -1;
  return std::pair<int,bool>(static_cast<int>(l), true);
}

void ft_toUpper(std::string& str) {
  std::string::iterator it;
  for (it=str.begin(); it!=str.end(); ++it) {
    if ('a' <= *it && *it <= 'z')
      *it = (*it - 32);
  }
}

void ft_toLower(std::string& str) {
  std::string::iterator it;
  for (it=str.begin(); it!=str.end(); ++it) {
    if ('A' <= *it && *it <= 'Z')
      *it = (*it + 32);
  }
}

const std::string& getLocalHostname() {
  static std::string hostname;
  if (hostname.empty()) {
    char name[HOST_NAME_MAX+1];
    std::memset(name, 0, sizeof(name));
    if (gethostname(name, sizeof(name)) == 0)
      hostname = name;
    else
      hostname = "Undefined";
  }
  return hostname;
}

std::vector<string> split(string s, const string& delimiter) {
    std::vector<string> tokens;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
}

// :ngircd.none.net 421 mvg xxxx :Unknown command
const string genErrUnknownCommand(const string& serverName,
  const string& commandString) {
  std::ostringstream oss;
  oss << ':' << serverName 
    << ' ' << ERR_UNKNOWNCOMMAND 
    << ' ' << commandString
    << " :Unknown command\r\n";
  return oss.str();
}

// :ngircd.none.net 461 mv user :Syntax error
const string genSyntaxError(const string& serverName,
  const string& nickName, const string& cmd) {
  std::ostringstream oss;
  oss << ':' << serverName 
    << ' ' << ERR_NEEDMOREPARAMS 
    << ' ' << nickName
    << ' ' << cmd
    << " :Syntax error\r\n";
  return oss.str();
}

