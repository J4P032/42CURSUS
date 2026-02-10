/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:05:14 by user1             #+#    #+#             */
/*   Updated: 2026/02/08 17:11:19 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <set>
#include <string>
#include <vector>

#define GREEN_TEXT "\033[1;32m"
#define RESET_COLOR "\033[0m"

using std::string;
typedef std::set<string>::const_iterator setOfStringsIterator;
typedef std::pair<setOfStringsIterator, setOfStringsIterator> pairIterators;

bool ft_isLetter(char c);
bool ft_isDigit(char c);
bool ft_isSpecial(char c);
string ft_itoa(int n);
std::pair<int, bool> ft_atoi(const string& str);
void ft_toUpper(string& str);
void ft_toLower(string& str);
const string& getLocalHostname();

const string genErrNeedMoreParams(const string& serverName,
  const string& nickName);

const string genErrUnknownCommand(const string& serverName,
  const string& commandString);

std::vector<string> split(string s, const string& delimiter);  
#endif