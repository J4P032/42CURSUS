/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:40:53 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/23 13:44:44 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_TPP
# define ARRAY_TPP

template <typename T>
Array<T>::Array(void) : _data(0), _size(0) {}


template <typename T>
Array<T>::Array(unsigned int n) : _data(new T[n]), _size(n){}

template <typename T>
Array<T>::Array(const Array<T>& other) : _data(new T[other._size]), _size(other._size){
	for (unsigned int i = 0; i < other._size; i++){
		this->_data[i] = other._data[i];
	}
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other){
	if (this == &other)
		return (*this);
	if (_data){ //para evitar fugas de memoria si nos pasan una dirección reservada.
		delete[] _data; //es una matriz por lo tanto con []
		_data = NULL;		
	}
	_size = other._size;
	_data = new T[other._size];
	for (unsigned int i = 0; i < other._size; i++){
		_data[i] = other._data[i];
	}
	return (*this);	
}

template <typename T>
Array<T>::~Array(void){
	if (_data){
		delete[] _data;
	}
}

#endif
