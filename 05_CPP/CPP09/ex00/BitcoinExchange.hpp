/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:20:49 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/30 18:51:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>

class	BitcoinExchange{
public:
	std::map<std::string, float> _data;

public:
	BitcoinExchange(void);
	BitcoinExchange(const std::string&);
	BitcoinExchange(const BitcoinExchange&);
	BitcoinExchange& operator=(const BitcoinExchange&);
	~BitcoinExchange(void);
};


bool	is_valid_date(int, int, int);
bool	is_valid_year(int);
bool	is_valid_month(int);
bool	is_valid_day(int, int, int);



#endif