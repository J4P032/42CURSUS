/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:43:04 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/13 11:20:30 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <stack>

/*STACK es junto con QUEUE un adaptador de contenedores. Son una "capa" que envuelve
a otro contenedor que en el caso de STACK suele ser un DEQUE, para limitar su
comportamiento y que solo se comporte como una pila. Por que STACK no permite
el acceso a todos sus elementos (con iteradores) sino que solo a su elemento frontal
de tal forma que para acceder a todos hay que usar .top() para verlo y luego destruirlo
con .pop() quedando el siguiente ".top()" visible. Pero es que por debajo suele ser un 
DEQUE.
Por eso al heredar de la clase std::stack estamos obteniendo acceso al contenedor PROTECTED
que por convención se llama "c". Y para tener acceso a dicho "c" que tipo es (DEQUE, LIST, VECTOR)
y por lo tanto a sus iteradores con métodos .begin(), .end(), etc... declaramos el typedef
de container_type para tener dicho iterador aplicado a dicho contenedor por debajo que existe.*/
template <typename T>
class MutantStack : public std::stack<T>{
public:
	typedef typename std::stack<T>::container_type::iterator iterator;
	typedef typename std::stack<T>::container_type::const_iterator const_iterator;
	typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
	typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;
	
	MutantStack(void){}
	MutantStack(T element) {
		this->push(element);
	}
	MutantStack(const MutantStack<T>& other) : std::stack<T>(other){}
	MutantStack& operator=(const MutantStack& other){
		if (this != &other)
			std::stack<T>::operator=(other);
		return (*this);
	}
	~MutantStack(void){}

	template <typename C>
	MutantStack(C begin, C end){
		while (begin != end){
			this->push(*begin);
			++begin;
		}
	}

//ITERADORES
/*al principio declaré los typedef de arriba como it, cit, rit o crit pero el main no compila
por que cuando hace MutantStack<int>::iterator se refiere a este nombre si no tendría que ser
MutantStack<int>::it y como viene como viene el main pues lo dejo con el nombre largo que además
es el nombre normal que se usa.*/
	iterator				begin(){return this->c.begin();}
	const_iterator			begin() const{return this->c.begin();}
	iterator				end(){return this->c.end();}
	const_iterator			end() const{return this->c.end();}
	reverse_iterator		rbegin(){return this->c.rbegin();}
	const_reverse_iterator	rbegin() const{return this->c.rbegin();}
	reverse_iterator		rend(){return this->c.rend();}
	const_reverse_iterator	rend() const{return this->c.rend();}
};

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const MutantStack<T>& other){
	typename MutantStack<T>::const_iterator it = other.begin();
	while (it != other.end()){
		if (it != other.begin())
			out << ",";
		out << *it ;
		++it;
	}
	return (out);
}


#endif
