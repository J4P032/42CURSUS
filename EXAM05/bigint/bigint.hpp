/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:33:03 by jrollon-          #+#    #+#             */
/*   Updated: 2026/02/25 16:45:48 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <vector>

class bigint{
public:
	bigint() {}
	
	template <typename T>
	bigint(T n){
		if (n == 0)
			_BN.insert(_BN.begin(), 0);
		while (n > 0){
			int aux = n % 10;
			_BN.insert(_BN.begin(), aux);
			n /= 10;
		}
	}
	
	bigint(const bigint& other) : _BN(other.getBN()){}

	bigint& operator=(const bigint& other){
		_BN = other.getBN();
		return (*this);
	}

	bigint operator+(const bigint& other) const{
		bigint	aux;
		int		suma = 0;
		int		add = 0;
		std::vector<int>::const_reverse_iterator it_first = _BN.rbegin();
		std::vector<int>::const_reverse_iterator it_second = other._BN.rbegin();
		
		while (it_first != _BN.rend() && it_second != other._BN.rend()){
			suma = *it_first + *it_second + add;
			add = 0; //resetearlo
			if (suma > 9){
				suma %= 10;
				add = 1;
			}
			it_second++;
			it_first++;
			aux._BN.insert(aux._BN.begin(), suma);
		}
		while (it_first != _BN.rend()){
			suma = *it_first + add;
			add = 0; //resetearlo
			if (suma > 9){
				suma %= 10;
				add = 1;
			}
			it_first++;
			aux._BN.insert(aux._BN.begin(), suma);
		}
		while (it_second != other._BN.rend()){
			suma = *it_second + add;
			add = 0; //resetearlo
			if (suma > 9){
				suma %= 10;
				add = 1;
			}
			it_second++;
			aux._BN.insert(aux._BN.begin(), suma);
		}
		if (add) //el resto final añade uno.
			aux._BN.insert(aux._BN.begin(), 1);
		return (aux);
	}
	
	std::vector<int> getBN(void) const{
		return (_BN);
	}
	
private:
	std::vector<int> _BN;

};

std::ostream& operator<<(std::ostream& out, const bigint& obj){
	std::vector<int>	aux_vec;
	aux_vec = obj.getBN();
	std::vector<int>::const_iterator it = aux_vec.begin();
	if (it != aux_vec.end()){
		for (;it != aux_vec.end(); ++it){
			std::cout << *it;
		}
	}
	return (out);
}


#endif
