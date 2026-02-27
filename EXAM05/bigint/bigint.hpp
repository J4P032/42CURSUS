/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:33:03 by jrollon-          #+#    #+#             */
/*   Updated: 2026/02/27 17:10:54 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <algorithm> //std::reverse
# include <vector>

/*
Regla mnemotécnica para el examen:

Si el operador tiene un = (como +=, -=, <<=, >>=), NUNCA pongas const al final y SIEMPRE usa return *this; lleva &
Si el operador NO tiene un = (como +, -, <<, >>, ==, <), SIEMPRE pon const al final y devuelve una copia nueva.


*/


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

	~bigint(void){}
	
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

	bigint& operator+=(const bigint& other){
		*this = *this + other;
		return (*this);
	}
	
/* 	bool	operator==(const bigint& other) const{
		if (_BI.size() != other._BI.size())
			return (false);
		
		std::vector<int>::const_iterator it_first = _BI.begin();
		std::vector<int>::const_iterator it_second = other._BI.begin();
		while (it_first != _BI.end() && it_second != other._BI.end()){
			if (*it_first != *it_second)
				return (false);
			it_first++;
			it_second++;
		}
		return (true);
	} */
	
	bool	operator==(const bigint& other) const{
		return (_BI == other._BI); //por que en vector ya está el operador== implementado. Dejo lo de arriba comentado para ver como se haría.
	}

	bool	operator!=(const bigint& other)const{
		return !(*this == other); //ya que esta definido el operator== para la clase, puedo implemtar el != 
	}

	bool	operator<(const bigint& other) const{
		if (_BI.size() != other._BI.size())
			return (_BI.size() < other._BI.size());
		return (_BI < other._BI);
	}
	
	bool	operator<=(const bigint& other) const{
		return (*this < other || *this == other);
	}
	
	bool	operator>(const bigint& other) const{
		return (other < *this);
	}

	bool	operator>=(const bigint& other) const{
		return !(*this < other);
	}

	

	bigint	operator<<(int n) const{
		if (n <= 0)
			return (*this) ;
		bigint result(*this);
		if (result._BI.empty()){
			result._BI.push_back(0);
			return (result);
		}
		if (result._BI.size() == 1 && result._BI[0] == 0)
			return (result);
		for (int i = 0; i < n; i++){
			result._BI.push_back(0);
		}
		return (result);
	}

	bigint&	operator<<=(int n){
		*this = *this << n;
		return (*this);
	}

	bigint&	operator>>=(int n){
		*this = *this >> n;
		return (*this);
	}


	bigint	operator>>(int n) const{
		if (n <= 0)
			return (*this);
		bigint res(*this);
		if (res._BI.empty()){
			res._BI.push_back(0);
			return (res);
		}
		if (_BI.size() == 1 && _BI[0] == 0)
			return (*this);
		for (int i = 0; i < n && !res._BI.empty(); i++){
			res._BI.pop_back();
		}
		if (res._BI.empty())
			res._BI.push_back(0);
		return (res);
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
