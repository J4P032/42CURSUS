/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:39:48 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/26 14:23:54 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>
# include <stdexcept> //para lanzar std::out_of_range

template <typename T>
class Array{
	public:
	Array(void); //crea un Array vacio
	Array(unsigned int n); //crea Array de n elementos inicializados como default
	Array(const Array<T>& other); //copia con new (malloc)
	Array<T>& operator=(const Array<T>& other); //copia con new
	~Array(void);

	//getter
	unsigned int	getSize(void) const;

	//operadores
	T& operator[](unsigned int index);
	const T& operator[](unsigned int index) const;
	/*hay un no const, por que si hago array[num] = algo, lo estoy modificando
	el const, es necesario en este caso por que al usar el operador<< este le estoy
	pasando un const Array<T> &array como segundo parametro y claro... necesita un objeto
	que no se pueda alterar para el operador[]. Por el resto es lo mismo dentro*/
	
	private:
	T*				_data;
	unsigned int	_size;
	
};

template <typename T>
std::ostream &operator<<(const std::ostream &out, const Array<T> &array);

# include "Array.tpp" //tiene que ir al final, por que si no se menciona un Array que no existe.

#endif
