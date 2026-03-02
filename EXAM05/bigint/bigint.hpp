/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:33:03 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/03 00:44:19 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <algorithm>
# include <vector>

inline bool is_digit(char c){
    return (c >= '0' && c <= '9');
}

inline int  ft_atoi(char c){
    return (c - '0');
}

class bigint{
public:

//CONSTRUCTORES
	bigint(void){}
    
    bigint(long num){
        if (num == 0)
            _BI.push_back(0);
        while (num > 0){
            _BI.push_back(num%10);
            num /= 10;
        }
        if (_BI.empty())
            _BI.push_back(0);
        std::reverse(_BI.begin(), _BI.end());
    }

	 bigint(int num){ //se necesita por que bigint(0) podria ser como bigint(NULL) que es un bigint(char *) y no sabe cual pillar
		*this = bigint((long)num);
	}

    bigint(const std::string& str){
        std::string::const_iterator it = str.begin();
        while (it != str.end() && *it == '0')
            it++;
		if (it == str.end()){
			_BI.push_back(0);
			return ;
		}
        while (it != str.end() && is_digit(*it)){
            _BI.push_back(ft_atoi(*it));
            it++;
        }
    }

	bigint(const char* str){
		*this = bigint(std::string(str));
	}

//COPIA

	bigint(const bigint& other) : _BI(other._BI){}

	bigint&	operator=(const bigint& other){
		if (this != &other)
			_BI = other._BI;
		return (*this);
	}

//DESTRUCTOR
	~bigint(){}

//COMPARACIONES
	bool	operator==(const bigint& other) const{
		return (_BI == other._BI);
	}

	bool	operator!=(const bigint& other) const{
		return !(_BI == other._BI);
	}

	bool	operator<(const bigint& other) const{
		if (_BI.size() != other._BI.size())
			return (_BI.size() < other._BI.size());
		return (_BI < other._BI);
	}

	bool	operator<=(const bigint& other) const{
		if (*this < other)
			return (true);
		if (*this == other)
			return (true);
		return (false);
	}

	bool	operator>(const bigint& other) const{
		return (other < *this);
	}

	bool	operator>=(const bigint& other) const{
		if (*this > other)
			return (true);
		if (*this == other)
			return (true);
		return (false);
	}

//shift
bigint operator<<(int n) const{
	bigint aux(*this);

	if (n <= 0)
		return (aux);
	if (aux._BI.size() == 1 && aux._BI.at(0) == 0)
		return (aux);
	if (aux._BI.empty()){
		aux._BI.push_back(0);
		return (aux);
	}
	for (int i = 0; i < n; i++){
		aux._BI.push_back(0);
	}
	return (aux);
}

bigint& operator<<=(int n){
	*this = *this << n;
	return (*this);
}

bigint operator>>(int n) const{
	bigint aux(*this);
	if (n <= 0)
		return (aux);
	if (!aux._BI.empty() && aux._BI.at(0) == 0)
		return (aux);
	for (int i = 0; i < n && !aux._BI.empty(); i++)
		aux._BI.pop_back();
	
	if (aux._BI.empty())
		aux._BI.push_back(0);
	return (aux);
}

bigint& operator>>=(int n){
	*this = *this >> n;
	return (*this);
}

bigint operator<<(const bigint& other) const{
	bigint aux(*this);
	if (other._BI.empty()){
		aux._BI.push_back(0);
		return (aux);
	}
	if (other == 0)
		return (aux);
	for (bigint i(0); i < other; ++i){
		aux._BI.push_back(0);
	}
	return (aux);
}

bigint& operator<<=(const bigint& other){
	*this = *this << other;
	return (*this);
}

bigint operator>>(const bigint& other) const{
	bigint aux(*this);
	if (other._BI.empty()){
		aux._BI.push_back(0);
		return (aux);
	}
	if (other == 0)
		return (aux);
	for (bigint i(0); i < other && !aux._BI.empty(); ++i){
		aux._BI.pop_back();
	}
	if (aux._BI.empty())
		aux._BI.push_back(0);
	return (aux);
}

bigint& operator>>=(const bigint& other){
	*this = *this >> other;
	return (*this);
}




//OPERATOR ADD
	bigint	operator+(const bigint& other) const{
		std::vector<int>::const_reverse_iterator itl = _BI.rbegin();
		std::vector<int>::const_reverse_iterator itr = other._BI.rbegin();
		int		resto = 0;
		int 	aux = 0;
		bigint	suma;

		while (itl != _BI.rend() && itr != other._BI.rend()){
			aux = *itl + *itr + resto;
			resto = 0; //reset de resto
			if (aux > 9){
				suma._BI.push_back(aux%10);
				resto = 1;
			}
			else
				suma._BI.push_back(aux);
			itl++;
			itr++;
		}
		while (itl != _BI.rend()){
			aux = *itl + resto;
			resto = 0;
			if (aux > 9){
				suma._BI.push_back(aux%10);
				resto = 1;
			}
			else
				suma._BI.push_back(aux);
			itl++;
		}
		while (itr != other._BI.rend()){
			aux = *itr + resto;
			resto = 0;
			if (aux > 9){
				suma._BI.push_back(aux%10);
				resto = 1;
			}
			else
				suma._BI.push_back(aux);
			itr++;
		}
		if (resto)
			suma._BI.push_back(1);
		std::reverse(suma._BI.begin(), suma._BI.end());

		return (suma);
	}

	bigint&	operator+=(const bigint& other){
		*this = *this + other;
		return (*this);
	}

	bigint&	operator++(){
		*this += 1;
		return (*this);
	}

	bigint	operator++(int){
		bigint unidad(1);
		bigint aux(*this);
		*this = *this + unidad;
		return (aux);
	}


//GETTERS

	const std::vector<int>& get_BI() const{
    	return (_BI);
}

private:
    std::vector<int> _BI;

};

inline  std::ostream& operator<<(std::ostream& out, const bigint& obj){
    const std::vector<int>&    aux = obj.get_BI();
    std::vector<int>::const_iterator it = aux.begin();
    while (it != aux.end()){
        out << *it;
        it++;
    }
    return (out);
}


#endif
