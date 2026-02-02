/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:40:53 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/26 14:42:41 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_TPP
# define ARRAY_TPP

template <typename T>
Array<T>::Array(void) : _data(0), _size(0) {}


template <typename T>
Array<T>::Array(unsigned int n) : _data(new T[n]), _size(n){
	for (unsigned int i = 0; i < n; i++)
		_data[i] = T(); //llamamos al constructor por defecto del tipo T. Int para constructor de ints.
}						//Para tipos básicos como int, deja el valor en 0; para punteros, deja nullptr (o 0 en C++98); para clases, llama a su constructor vacío.

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

template <typename T>
unsigned int Array<T>::getSize(void) const{
	return (_size);
}

template <typename T>
T& Array<T>::operator[](unsigned int index){
	if (index >= _size)
		throw std::out_of_range("Index out of range");
	return (_data[index]);
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const{
	if (index >= _size)
		throw std::out_of_range("Index out of range");
	return (_data[index]);
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Array<T> &array){
	out << "[";
	for (unsigned int i = 0; i < array.getSize(); i++){
		if (i != 0) out << ", ";
		out << array[i];
	};
	out << "]";
	return (out);
}



#endif
