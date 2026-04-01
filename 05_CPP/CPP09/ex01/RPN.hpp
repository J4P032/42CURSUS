/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:41:05 by jrollon-          #+#    #+#             */
/*   Updated: 2026/04/01 16:26:52 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <iostream>

class RPN{
private:
	std::stack<int>	_nums;

public:
	RPN(void);
	RPN(const RPN&);
	RPN&	operator=(const RPN&);
	~RPN(void);

	int					process(const char*);
	std::stack<int>		getNums(void) const;
};

int		operate(std::stack<int>&, char);
bool	isOperator(char c);

#endif