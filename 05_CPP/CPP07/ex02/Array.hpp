/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:39:48 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/23 13:47:13 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>

template <typename T>
class Array{
	public:
	Array(void); //crea un Array vacio
	Array(unsigned int n); //crea Array de n elementos inicializados como default
	Array(const Array<T>& other); //copia con new (malloc)
	Array<T>& operator=(const Array<T>& other); //copia con new
	~Array(void);
	
	private:
	T*				_data;
	unsigned int	_size;
	
};

# include "Array.tpp" //tiene que ir al final, por que si no se menciona un Array que no existe.

#endif
