/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:04:35 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/04 15:23:07 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <iterator>
# include <iostream>
# include <typeinfo> //uso de typeid

class NotFoundException : public std::exception{
public:	
	virtual const char* what() const throw(){ //throw() para no lanzar excepcion ella misma.
		return "Element not found in container";
	}
};

template <typename T>
void	fill_container(T& c){
	std::back_insert_iterator<T> it = std::back_inserter(c);
	
	for (size_t i = 0; i < 100; ++i){
		*it = i;
	}
}

template <typename T>
void	print_container(const T& c){
	typename T::const_iterator it = c.begin();
	std::cout << std::endl << "// ";
	if (std::string(typeid(c).name()) == "St6vectorIiSaIiEE")
		std::cout << "VECTOR" << std::endl;
	for (; it != c.end(); ++it){
		if (it != c.begin()) //list no admite (it + 1) por eso se pone delante la coma
			std::cout << ',';
		std::cout << *it;
	}
	std::cout << std::endl;
}

template <typename T>
void	easyfind(const T& container, int n){
	//necesita "typename" por que si no no sabe si se le manda un tipo (int, vector, etc)
	//variable o función incluida en T.
	typename T::const_iterator it = std::find(container.begin(), container.end(), n);
	if (it == container.end())
		throw NotFoundException();
	else
		std::cout << "número " << n << " encontrado en el contenedor." << std::endl;
}

#endif
