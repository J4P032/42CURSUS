/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvassall <mvassall@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:05:14 by user1             #+#    #+#             */
/*   Updated: 2026/02/02 15:52:08 by mvassall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <set>
#include <string>

#define GREEN_TEXT "\033[1;32m"
#define RESET_COLOR "\033[0m"

typedef std::set<std::string>::const_iterator setOfStringsIterator;
typedef std::pair<setOfStringsIterator, setOfStringsIterator> pairIterators;

bool ft_isLetter(char c);
bool ft_isDigit(char c);
bool ft_isSpecial(char c);
std::string ft_itoa(int n);
std::pair<int, bool> ft_atoi(const std::string& str);
void ft_toUpper(std::string& str);
const std::string& getLocalHostname();
#endif