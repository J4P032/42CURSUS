/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 08:57:08 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/16 19:30:41 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

int Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

// *****************************************************
// CONSTRUCTORS & DESTRUCTORS **************************
// *****************************************************

Account::Account( int initial_deposit )
{
	Account::_displayTimestamp();
	this->_accountIndex = Account::_nbAccounts;
	
	std::cout << "index:" << this->_accountIndex << ";amount:" << initial_deposit;
	std::cout << ";created" << std::endl; 
	Account::_nbAccounts++;
	this->_amount = initial_deposit;
	Account::_totalAmount += initial_deposit;
	this->_nbDeposits = 0;
	this->_nbWithdrawals = 0;
}	

Account::~Account( void )
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "amount:" << this->checkAmount() << ";";
	std::cout << "closed" << std::endl;
}

// *****************************************************
// GETTERS *********************************************
// *****************************************************

int	Account::getNbAccounts( void )
{
	return (Account::_nbAccounts);
}

int	Account::getTotalAmount( void )
{
	return (Account::_totalAmount);
}

int	Account::getNbDeposits( void )
{
	return (Account::_totalNbDeposits);
}

int	Account::getNbWithdrawals( void )
{
	return (Account::_totalNbWithdrawals);
}

void	Account::displayAccountsInfos( void )
{
	Account::_displayTimestamp();
	std::cout << "accounts:" << getNbAccounts() << ";";
	std::cout << "total:" << getTotalAmount() << ";";
	std::cout << "deposits:" << getNbDeposits() << ";";
	std::cout << "withdrawals:" << getNbWithdrawals() << std::endl;
}

int		Account::checkAmount( void ) const
{
	return (this->_amount);
}

void	Account::displayStatus( void ) const
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "amount:" << this->checkAmount() << ";";
	std::cout << "deposits:" << this->_nbDeposits << ";";
	std::cout << "withdrawals:" << this->_nbWithdrawals;
	std::cout << std::endl;
}


// *****************************************************
// SETTERS *********************************************
// *****************************************************

void	Account::makeDeposit( int deposit )
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "p_amount:" << this->checkAmount() << ";";
	this->_amount += deposit;
	std::cout << "deposit:" << deposit << ";";
	std::cout << "amount:" << this->checkAmount() << ";";
	if (deposit > 0)
	{
		this->_nbDeposits++;
		Account::_totalNbDeposits++;
	}
	std::cout << "nb_deposits:" << this->_nbDeposits;
	std::cout << std::endl;
	Account::_totalAmount += deposit;
}

bool	Account::makeWithdrawal( int withdrawal )
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "p_amount:" << this->checkAmount() << ";";
	std::cout << "withdrawal:";
	if (withdrawal > this->checkAmount())
	{
		std::cout << "refused" << std::endl;
		return (false);
	}
	this->_amount -= withdrawal;
	std::cout << withdrawal << ";";
	std::cout << "amount:" << this->checkAmount() << ";";
	this->_nbWithdrawals++;
	Account::_totalNbWithdrawals++;
	std::cout << "nb_withdrawals:" << this->_nbWithdrawals;
	std::cout << std::endl;
	Account::_totalAmount -= withdrawal;
	return (true);
}


// *****************************************************
// PRIVATE *********************************************
// *****************************************************

/*setw(2) and setfill('0') to fill in case January = 1 -> 01*/
void	Account::_displayTimestamp(void)
{
	std::time_t time_now = std::time(NULL); //seconds since 1970 
	std::tm		*today = std::localtime(&time_now); //struct with ints nums desglosed from seconds since 1970
	std::cout << "[" << today->tm_year + 1900; // years since 1900
	std::cout << std::setw(2) << std::setfill('0') << today->tm_mon + 1; // January is 0
	std::cout << std::setw(2) << std::setfill('0') << today->tm_mday;
	std::cout << "_";
	std::cout << std::setw(2) << std::setfill('0') << today->tm_hour;
	std::cout << std::setw(2) << std::setfill('0') << today->tm_min;
	std::cout << std::setw(2) << std::setfill('0') << today->tm_sec;
	std::cout << "] ";
}

Account::Account( void )
{

	
}
