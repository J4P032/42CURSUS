/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:45:42 by jrollon-          #+#    #+#             */
/*   Updated: 2026/04/01 16:35:40 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool	isOperator(char c){
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int	operate(std::stack<int>& st, char c){
	int	A;
	int B;
	int result;
	
	if (st.size() > 1){
		B = st.top();
		st.pop();
		A = st.top();
		st.pop();
		switch (c){
			case '+':
				result = A + B;
				break;
			case '-':
				result = A - B;
				break;
			case '*':
				result = A * B;
				break;
			case '/':
				if (B != 0){
					result = A / B;
					break;
				}
				else
					return 0;
		}
		st.push(result);
		return 1;
	}
	else
		return 0;
}

RPN::RPN(void){}

RPN::RPN(const RPN& other) : _nums(other._nums){}

RPN& RPN::operator=(const RPN& other){
	if (this != &other)
		_nums = other._nums;
	return (*this);
}

RPN::~RPN(void){}

int	RPN::process(const char* str){
	int		chars = 0;
	size_t	i	= 0;
	
	while (str && str[i]){
		if (str[i] == ' '){
			i++;
			chars = 0;
			continue ;
		}
		if (isdigit(str[i]) && chars == 0){
			_nums.push(str[i] - '0');
			chars++;
			i++;
			continue;
		}
		else if (chars > 0)
			return 0;
		
		if (isOperator(str[i])){
			chars++;
			if (!operate(_nums, str[i]))
				return 0;
		}
		else
			return 0;
		i++;
	}
	if (_nums.size() == 1)
		return 1;
	return 0;
}

std::stack<int> RPN::getNums(void) const{
	return (_nums);
}