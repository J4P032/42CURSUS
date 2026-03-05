/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:41:00 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/05 21:08:06 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>

inline void	reverse_str(std::string& s){
	int len = s.length();
	if (len == 0)
		return;
	
	std::string aux = s;
	s.clear();
	for (int i = len - 1; i > -1; --i){
		s += aux[i];
	}
}

inline bool	is_digit(char c){
	return (c >= '0' && c <= '9');
}

inline int	ft_atoi(char c){
	return (c - '0');
}

class bigint{
public:
	bigint(void) : _BI("0"){}

	bigint(unsigned long n){
		if (n == 0){
			_BI = "0";
			return; 
		}
		while (n > 0){
			_BI += n%10 + '0';
			n /= 10;
		}
		if (_BI.empty())
			_BI = "0";
		reverse_str(_BI);
	}

	bigint(std::string& s){
		
		while (!s.empty() && s[0] == '0')
			s.erase(0, 1);
				
		int	len = s.length();
		
		for (int i = 0; i < len; ++i){
			if (!is_digit(s[i])){
				_BI = "0";
				return;
			}
			_BI += s[i]; 
		}
	}

	bigint(const char* s){
		size_t i = 0;

		while (s && s[i] == '0')
			i++;
		while (s && s[i] != '\0'){
			if (!is_digit(s[i])){
				_BI = "0";
				return;
			}
			_BI += s[i];
			i++;
		}
	}

	bigint(int n) {
    	if (n <= 0) {
        	_BI = "0";
        	return;
    	}
    	long ln = n;
    	while (ln > 0) {
        	_BI += (ln % 10) + '0';
        	ln /= 10;
    	}
    	reverse_str(_BI);
	}

	bigint(const bigint& other) : _BI(other._BI) {}

	bigint& operator=(const bigint& other){
		if (this != &other)
			_BI = other._BI;
		return (*this);
	}

	~bigint(void){}


//+
	bigint	operator+(const bigint& other) const{
		bigint aux;
		aux._BI.clear();
		int		l = _BI.length();
		int		r = other._BI.length();
		int		resto = 0;
		int		suma = 0;
		
		while (l > 0 && r > 0){
			suma = ft_atoi(_BI[l - 1]) + ft_atoi(other._BI[r - 1]) + resto;
			resto = 0; //reset
			if (suma > 9){
				aux._BI += suma%10 + '0';
				resto = 1;
			}
			else
				aux._BI += suma + '0';
			l--;
			r--;
		}

		while (l > 0){
			suma = ft_atoi(_BI[l - 1]) + resto;
			resto = 0; //reset
			if (suma > 9){
				aux._BI += suma%10 + '0';
				resto = 1;
			}
			else
				aux._BI += suma + '0';
			l--;
		}

		while (r > 0){
			suma = ft_atoi(other._BI[r - 1]) + resto;
			resto = 0; //reset
			if (suma > 9){
				aux._BI += suma%10 + '0';
				resto = 1;
			}
			else
				aux._BI += suma + '0';
			r--;
		}

		if (resto)
			aux._BI += '1';
		
		reverse_str(aux._BI);
		return (aux);
	}

	bigint& operator+=(const bigint& other){
		*this = *this + other;
		return (*this);
	}
	
	bigint& operator++(){
		bigint unit(1);
		*this = *this + unit;
		return (*this); 
	}

	bigint	operator++(int){
		bigint aux(*this);
		++*this;
		return (aux);
	}

//SWIFTING
	bigint	operator<<(int n) const{
		bigint aux(*this);
		
		if (n <= 0)
			return (aux);
		if (aux._BI == ""){
			aux._BI = "0";
			return (aux);
		}
		if (aux._BI == "0"){
			return (aux);	
		}
		for (int i = 0; i < n; ++i){
			aux._BI += '0';
		}
		return (aux);
	}

	bigint& operator<<=(int n){
		*this = *this << n;
		return (*this);
	}

	bigint	operator<<(const bigint& other) const{
		bigint aux(*this);
		
		if (other._BI == "0")
			return (aux);
		if (aux._BI == ""){
			aux._BI = "0";
			return (aux);
		}
		if (aux._BI == "0"){
			return (aux);	
		}

		for (bigint i(0); i < other; ++i){
			aux._BI += '0';
		}
		return (aux);
	}

	bigint&	operator<<=(const bigint& other){
		*this = *this << other;
		return (*this);
	}

	bigint	operator>>(int n) const{
		bigint aux(*this);
		int len = aux._BI.length();
		
		if (n <= 0)
			return (aux);
		if (aux._BI == ""){
			aux._BI = "0";
			return (aux);
		}
		if (aux._BI == "0"){
			return (aux);	
		}

		int	remove = len - n;
		if (remove <= 0){
			aux._BI = "0";
			return (aux);
		}
		
		bigint aux2;
		aux2._BI.clear();
		for (int i = 0; i < remove; ++i){
			aux2._BI += aux._BI[i];
		}
		return (aux2);
	}

	bigint& operator>>=(int n){
		*this = *this >> n;
		return (*this);
	}

	bigint	operator>>=(const bigint& other){
		bigint aux(*this);
		int len = aux._BI.length();
		
		if (other._BI == "0")
			return (aux);
		if (aux._BI == ""){
			aux._BI = "0";
			return (aux);
		}
		if (aux._BI == "0"){
			return (aux);	
		}

		/////////
		
		bigint	remove = bigint(len) - other;
		if (remove <= bigint(0)){
			aux._BI = "0";
			return (aux);
		}
		
		bigint aux2;
		aux2._BI.clear();
		for (bigint i(0); i < remove; ++i){
			aux2._BI += aux._BI[i];
		}
		return (aux2);
	}
	

//COMPARACION
	bool	operator==(const bigint& other) const{
		return (_BI == other._BI);
	}

	bool	operator<(const bigint& other) const{
		if (_BI.length() == other._BI.length()){
			for (size_t i = 0; i < _BI.length(); ++i){
				if (_BI[i] < other._BI[i])
					return (true);
			}
			return (false);
		}
		return (_BI.length() < other._BI.length());
	}


//GETTERS
	const std::string& getBI() const{
		return (_BI);
	}
private:
	std::string _BI;

};

inline std::ostream& operator<<(std::ostream& out, const bigint& obj){
	out << obj.getBI();
	return (out);
}

#endif