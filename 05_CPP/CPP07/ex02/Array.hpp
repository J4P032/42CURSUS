/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:39:48 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/21 17:35:46 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

template <typename T>
class Array{
public:
	Array(void); //crea un Array vacio
	Array(unsigned int n); //crea Array de n elementos inicializados como default
	Array(const Array<T>& other); //copia con new
	Array<T>& operator=(const Array<T>& other); //copia con new
	~Array(void);
	
private:
	T*				_data;
	unsigned int	_size;
	
};

# include "Array.tpp"

#endif
