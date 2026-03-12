/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:04:35 by jrollon-          #+#    #+#             */
/*   Updated: 2026/03/12 10:13:15 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <iostream>
# include <typeinfo> //uso de typeid
# include <stack>
# include <queue>

/*	¿Por qué definimos el método 'what' aquí y no en un .cpp?
       
       1. REGLA DE TEMPLATES: Esta excepción es lanzada por una función 'template'. 
          Las plantillas no son código real hasta que el compilador las "fabrica" 
          en el main.cpp. Para que el compilador pueda fabricar la función, 
          necesita tener TODO el código (incluida esta excepción) a la vista.
       
       2. EL ERROR DE ENLAZADO: Si el código de 'what()' estuviera en un .cpp aparte,
          el compilador del 'main' no encontraría la "vtable" (la firma de la clase)
          ni la información del tipo, provocando errores de "undefined reference".
       
       3. SOLUCIÓN: Al definir el método dentro de la clase en el .hpp, se vuelve 
          'inline'. Esto permite que el código esté disponible en cualquier archivo 
          que incluya este header, evitando fallos al compilar.
		  
	Nota: la hago canónica por el qué diran en 42, pero que no debería serlo ya que viene
	de std::exception que ya es canónica de por si, y además NotFoundException es una
	clase de apoyo para lanzar una excepción particular. No principal  */

class NotFoundException : public std::exception{
public:
	NotFoundException() throw() {}
	NotFoundException(const NotFoundException&) throw(){}
	NotFoundException& operator=(const NotFoundException&) throw(){return *this;}
	virtual ~NotFoundException() throw() {}	
	virtual const char* what() const throw(){ //throw() para no lanzar excepcion ella misma.
		return "Element not found in container. Program interrupt!!";
	}
};

//Vector, list y deque permiten push_back()
template <typename T>
void	fill_container(T& c, size_t size, bool decimal){
	for (size_t i = 0; i < size; ++i){
		if (decimal)
			c.push_back(i + 0.1);
		else
			c.push_back(i);
	}
}

//funcion rellenado para PASARELA de STACK o QUEUE que es la misma y así no repito código
template <typename C>
void do_fill(C& c, size_t size, bool decimal){
	for (size_t i = 0; i < size; ++i){
		if (decimal)
			c.push(i + 0.1);
		else
			c.push(i);
	}
}

//PASARELA
//stack y queue solo permiten push(). Overload de fill_container
template <typename T>
void	fill_container(std::stack<T>& c, size_t size, bool decimal){
	do_fill(c, size, decimal);	
}
template <typename T>
void	fill_container(std::queue<T>& c, size_t size, bool decimal){
	do_fill(c, size, decimal);	
}

//SOLO vector, list y deque.
template <typename T>
void	print_container(const T& c){
	typename T::const_iterator it = c.begin(); //ver lo de typename abajo.
	std::cout << std::endl << "// " << typeid(c).name() << std::endl;
	
	for (; it != c.end(); ++it){
		if (it != c.begin()) //list no admite (it + 1) por eso se pone delante la coma
			std::cout << ',';
		std::cout << *it;
	}
	std::cout << std::endl;
}

//stack.  Overload de print_container
//para imprimirlo se necesita destruir el contenedor ya que no hay iteradores.
//por lo que destruimos una copia. por eso no lleva &
/*OTRA COSA!! 
	como se puede ver print_container de stack y de queue SOLO difieren en c.top()
	y c.front(). Se podria pensar en hacer un do_print y desde una paralela, pasarle otro 
	parámetro que fuera seleccionable con un if si era uno u otro y asi no duplicar
	código. El problema es que al componer las funciones en compilación por el template
	NUNCA pasa por la lógica de un IF, y por lo tanto falla en la compilación diciendo
	que un método queue no tiene top() por ejemplo.*/
template <typename T>
void	print_container(std::stack<T> c){
	std::cout << std::endl << "// " << typeid(c).name() << std::endl;
	
	while (!c.empty()){
		std::cout << c.top(); //vemos el primer elemento
		std::cout << ',';
		c.pop(); //lo quitamos
	}
	std::cout << std::endl;
}

//stack.  Overload de print_container
//para imprimirlo se necesita destruir el contenedor ya que no hay iteradores.
//por lo que destruimos una copia. Por eso no lleva &
template <typename T>
void	print_container(std::queue<T> c){
	std::cout << std::endl << "// " << typeid(c).name() << std::endl;
	
	while (!c.empty()){
		std::cout << c.front(); //vemos el primer elemento
		std::cout << ',';
		c.pop(); //lo quitamos
	}
	std::cout << std::endl;
}


template <typename T>
typename T::iterator	easyfind(T& container, int n){
	/*necesita "typename" por que si no no sabe si se le manda un tipo (int, vector, etc)
	variable o función incluida en T.*/
	typename T::iterator it = std::find(container.begin(), container.end(), n);
	if (it == container.end())
		throw NotFoundException();
	std::cout << "Number " << n << " found in containter." << std::endl;
	return (it);
}

//overload de easyfind para stack y queue donde hay que destruir el contenedor para encontrarlo
//pero destruimos una copia. No se puede usar std::find por que depende de métodos que no tiene
template <typename T>
void	easyfind(std::stack<T> container, int n){
	while (!container.empty()){
		if (n == container.top()){
			std::cout << "Number " << n << " found in containter." << std::endl;
			return ; 
		}
		container.pop();
	}
	if (container.empty())
		throw NotFoundException();	
}

template <typename T>
void	easyfind(std::queue<T> container, int n){
	while (!container.empty()){
		if (n == container.front()){
			std::cout << "Number " << n << " found in containter." << std::endl;
			return ; 
		}
		container.pop();
	}
	if (container.empty())
		throw NotFoundException();	
}

#endif
