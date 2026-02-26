/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:33:03 by jrollon-          #+#    #+#             */
/*   Updated: 2026/02/26 14:31:07 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <algorithm> //std::reverse
# include <vector>

bool	is_digit(char c){
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char c){
	return (c - '0');
}

class bigint{
public:
	bigint(){}
	
	template<typename T>
	bigint(T n){
		if (n == 0)
			_BI.insert(_BI.begin(), 0);
		while (n > 0){
			_BI.insert(_BI.begin(), n%10);
			n /=10;
		}
		if (_BI.empty())
			_BI.push_back(0);
	}
	
	bigint(const std::string& n){
		std::string::const_iterator it = n.begin();
		bool	inicial = true;
		while (it != n.end() && is_digit(*it)){
			if (inicial){
				if (ft_atoi(*it) != 0){
					_BI.push_back(ft_atoi(*it));
					inicial = false;
				}
			}
			else
				_BI.push_back(ft_atoi(*it));
			it++;
		}
		if (_BI.empty())
			_BI.push_back(0);
	}
	
	bigint(const char* s){ //se le puede pasar como literal (bigint("123") y se iria al template.)
		*this = bigint(std::string(s));
	}

	bigint(const bigint& other) : _BI(other._BI){}

	bigint& operator=(const bigint& other){
		if (this != &other)
			_BI = other._BI;
		return (*this);
	}

	
	bigint operator+(const bigint& other) const{
		std::vector<int>::const_reverse_iterator it_first = _BI.rbegin();
		std::vector<int>::const_reverse_iterator it_second = other._BI.rbegin();
		bigint	suma;
		int		rest = 0;
		int		add = 0;

		while  (it_first != _BI.rend() && it_second != other._BI.rend()){
			add = *it_first + *it_second + rest;
			rest = 0; //reset
			if (add > 9){
				suma._BI.push_back(add%10); //lo montamos al reves, por O(1). Luego lo invertimos "reverse"
				rest = 1;
			}
			else
				suma._BI.push_back(add);
			it_first++;
			it_second++;
		}
		
		while  (it_first != _BI.rend()){
			add = *it_first + rest;
			rest = 0; //reset
			if (add > 9){
				suma._BI.push_back(add%10);
				rest = 1;
			}
			else
				suma._BI.push_back(add);
			it_first++;	
		}

		while  (it_second != other._BI.rend()){
			add = *it_second + rest;
			rest = 0; //reset
			if (add > 9){
				suma._BI.push_back(add%10);
				rest = 1;
			}
			else
				suma._BI.push_back(add);
			it_second++;	
		}
		if (rest)
			suma._BI.push_back(1);
		std::reverse(suma._BI.begin(), suma._BI.end()); //lo hemos montado al reves asi que lo invertimos. Podria haber hecho insert front, pero eso seria O(n2)
		return (suma);
	}
	
	const std::vector<int>&	getBI(void) const{
		return (_BI);
	}	
	
private:
	std::vector<int> _BI;
};

std::ostream& operator<<(std::ostream& out, const bigint& num){
	const std::vector<int>& bi_vector = num.getBI();
	std::vector<int>::const_iterator it = bi_vector.begin();
	while (it != bi_vector.end()){
		out << *it;
		it++;
	}
	return (out);
}

#endif
