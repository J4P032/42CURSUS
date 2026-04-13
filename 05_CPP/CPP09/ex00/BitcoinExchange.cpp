/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:26:34 by jrollon-          #+#    #+#             */
/*   Updated: 2026/04/13 16:43:22 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <iomanip>



bool	is_valid_month(int month){
	return (month > 0 && month < 13);
}

bool	is_valid_day(int year, int month, int day){
	if (day < 1 || day > 31)
		return (false);
	if (month == 2){
		if (day > 29)
			return (false);
		bool	bisiesto = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
		if (day == 29 && !bisiesto)
			return (false);
		return (true);
	}
	
	if (day == 31 && (month == 4 || month == 6 || month == 9 || month == 11))
		return (false);
	
	return (true);
}

//fecha inicial de bitcoin 2009-01-03
bool	is_valid_date(int year, int month, int day){
	return (is_valid_month(month) && is_valid_day(year, month, day));	
}

BitcoinExchange::BitcoinExchange(void){}

BitcoinExchange::BitcoinExchange(const std::string& datafile){
	std::ifstream file(datafile.c_str());  //no puede un std::string en C++98. En 11 sí. 
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database.");
	std::string	line;
	while (std::getline(file, line)){
		std::ostringstream	oss;
		std::string			year = "";
		std::string			month = "";
		std::string			day = "";
		std::string			date;
		int					num_decimals;
		double				bit_value = 0.0;
		oss.str("");
		oss.clear();
		
		std::string::const_iterator cit = line.begin();
		while (cit != line.end() && (std::isdigit(static_cast<unsigned char>(*cit)) || *cit == '-')){
			if (cit == line.begin() && *cit == '-')
				throw std::runtime_error("Error: negative year in database");
			if (!std::isdigit(static_cast<unsigned char>(*cit))) //each '-' or ',' I will advance it once. if not a number I jump over that line and continue to next.
				break ;
			if (!day.empty()) //in case there is no ',' at the end of the day but another '-'
				break ;
			oss << *cit;		
			cit++;
			if (cit != line.end() && *cit == '-'){
				if (year.empty())
					year = oss.str();
				else if (month.empty())
					month = oss.str();
				cit++;
				oss.str("");
				oss.clear();
			}
			else if (cit != line.end() && *cit == ','){
				day = oss.str();
				oss.str("");
				oss.clear();
			}
		}

		if (!is_valid_date(atoi(year.c_str()), atoi(month.c_str()), atoi(day.c_str())))
			continue ; //next line
		oss << year << "-" << month << "-" << day;
		date = oss.str();
		oss.str("");
		oss.clear();
		if (cit != line.end() && *cit == ',')
			cit++;
		else
			continue ;
		num_decimals = 0;
		while (cit != line.end() && (std::isdigit(static_cast<unsigned char>(*cit)) || *cit == '.')){
			if (*cit == '.')
				num_decimals++;
			oss << *cit;
			cit++;
		}
		if (cit != line.end() || num_decimals > 1) //there is another nonDigit after the numbers or after the ','
			continue ;
		if (oss.str() == "")
			continue ;
		bit_value = std::strtod(oss.str().c_str(), NULL);
		
		_data[date] = bit_value;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _data(other._data){}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other){
	if (this != &other)
		_data = other._data;
	return *this;
}

BitcoinExchange::~BitcoinExchange(void){}

void	BitcoinExchange::process_data(std::ifstream& file) const{
	std::string	line;
	std::getline(file, line);
	if (line != "date | value"){
		std::cerr << "Error: bad input => File has to start with line: 'date | value'" << std::endl;
		return ;
	}
	while (std::getline(file, line)){
		std::ostringstream	oss;
		std::string			year = "";
		std::string			month = "";
		std::string			day = "";
		std::string			date;
		int					num_decimals;
		double				value = 0.0;
		bool				negative;
		oss.str("");
		oss.clear();
		
		std::string::const_iterator cit = line.begin();
		while (cit != line.end() && (std::isdigit(static_cast<unsigned char>(*cit)) || *cit == '-')){
			if (cit == line.begin() && *cit == '-')
				break ;
			if (!std::isdigit(static_cast<unsigned char>(*cit))) //each '-' or ' ' I will advance it once. if not a number I jump over that line and continue to next.
				break ;
			if (!day.empty()) //in case there is no ' ' at the end of the day but another char non digit
				break ;
			oss << *cit;		
			cit++;
			if (cit != line.end() && *cit == '-'){
				if (year.empty()){
					if (oss.str().size() == 4)
						year = oss.str();
					else
						break ;
				}
				else if (month.empty()){
					if (oss.str().size() == 2)
						month = oss.str();
					else
						break ;
				}
				cit++;
				oss.str("");
				oss.clear();
			}
			else if (*cit == ' ' || cit == line.end()){
				if (oss.str().size() == 2) 
					day = oss.str();
				else
					break ;
				oss.str("");
				oss.clear();
			}
		}

		if (year.empty() || month.empty() || day.empty()){
			std::cerr << "Error: bad input => " << line << std::endl;
			continue ;
		}

		if (!is_valid_date(atoi(year.c_str()), atoi(month.c_str()), atoi(day.c_str()))){
			std::cerr << "Error: bad input => " << year << "-" << month << "-" << day << std::endl;
			continue ; //next line
		}
		oss << year << "-" << month << "-" << day;
		date = oss.str();
		oss.str("");
		oss.clear();
		if (cit != line.end() && *cit == ' '){
			cit++;
			if (cit != line.end() && *cit == '|'){
				cit++;
				if (cit != line.end() && *cit == ' ')
					cit++;
				else{
					std::cerr << "Error: bad input => Need space after '|'" << std::endl;
					continue ;
				}
			}
			else{
				std::cerr << "Error: bad input => After first space has to have an '|'" << std::endl;
				continue ;
			}
		}
		else{
			std::cerr << "Error: bad input => Need to have an space after the date" << std::endl;
			continue ;
		}
		num_decimals = 0;
		negative = false;
		if (*cit == '-')
			negative = true;
		while (cit != line.end() && (std::isdigit(static_cast<unsigned char>(*cit)) || *cit == '.')){
			if (*cit == '.')
				num_decimals++;
			oss << *cit;
			cit++;
		}
		if (negative){
			std::cerr << "Error: not a positive number." << std::endl;
			continue ;
		}
		if (cit != line.end() || num_decimals > 1){ //there is another nonDigit after the numbers or after the ' | '
			std::cerr << "Error: bad value => Value has to be only a float number." << std::endl;
			continue ;
		}
		if (oss.str() == ""){
			std::cerr << "Error: no value introduced after date => " << date << std::endl;
			continue ;
		}
		
		value = std::strtod(oss.str().c_str(), NULL);
		if (value == 1000){
			std::string s = oss.str();
			std::string::const_iterator its = s.begin();
			
			while (its != s.end() && *its != '.')
				its++;
			if (its != s.end() && *its == '.'){
				its++;
				while (its != s.end() && *its == '0')
					its++;
				if (its != s.end()){
					std::cerr << "Error: too large a number." << std::endl;
					continue ;
				}	
			}	
		}
		if (value > 1000){
			std::cerr << "Error: too large a number." << std::endl;
			continue ;
		}

		std::map<std::string, double>::const_iterator mit = _data.lower_bound(date);
		if (mit != _data.end() && mit->first == date){
			std::cout << std::fixed << std::setprecision(2);
			std::cout << date << " => " << value << " = " << (value * mit->second) << std::endl;
		}
		else if (mit != _data.begin()){
				--mit;
				std::cout << std::fixed << std::setprecision(2);
				std::cout << date << " => " << value << " = " << (value * mit->second) << std::endl;
		}
		else{
			std::cerr << "Error: date before all data.csv dates => " << date << "." << std::endl;
		}
	}
}	

const std::map<std::string, double>&	BitcoinExchange::get_data(void) const{
	return (this->_data);
}
