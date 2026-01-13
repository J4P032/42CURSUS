/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:10:26 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/13 10:39:15 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::~Base(void){}

A::A(void){
	std::cout << GREEN << "Instanced A." << RESET << std::endl;
}

B::B(void){
	std::cout << CYAN << "Instanced B." << RESET << std::endl;
}

C::C(void){
	std::cout << BLUE << "Instanced C." << RESET << std::endl;
}

Base* 	generate(void){
	int		randNum = std::rand() % 3; // 0 1 o 2
	Base	*aux; 
	switch (randNum){
		case 0:
			aux = new A();
			break;
		case 1:
			aux = new B();
			break;
		case 2:
			aux = new C();
			break;
		default:
			aux = NULL; //para no exportar direccion basura.
			break;
	}
	return (aux);
}

void	identify(Base* p){
	if (dynamic_cast<A*>(p)){
		std::cout << GREEN << "El Objeto es un A." << RESET << std::endl;
		return ;
	}
	else if (dynamic_cast<B*>(p)){
		std::cout << CYAN << "El Objecto es un B." << RESET << std::endl;
		return ;
	}
	else if (dynamic_cast<C*>(p)){
		std::cout << BLUE << "El Objecto es un C." << RESET << std::endl;
		return ;
	}
	std::cout << RED << "El Objecto NO es ni A, B o C." << RESET << std::endl;
}

void 	identify(Base& p){
	try{
		(void)dynamic_cast<A&>(p); //(void) por wall wextra werror 
		std::cout << GREEN << "El Objeto es un A (por Referencia)." << RESET << std::endl;
		return ;
	}
	catch(std::exception &ex){} //no puedo usar std::bad_cast por que deberia incluir <typeinfo> que no puedo por ejercicio. Pero esta es hija de std::exception
	try{
		(void)dynamic_cast<B&>(p);
		std::cout << CYAN << "El Objecto es un B (por referencia)." << RESET << std::endl;
		return ;
	}
	catch(std::exception &ex){}
	try{
		(void)dynamic_cast<C&>(p);
		std::cout << BLUE << "El Objecto es un C (por referencia)." << RESET << std::endl;
		return ;
	}	
	catch(std::exception &ex){}
	std::cout << RED << "El Objecto NO es ni A, B o C (por referencia)." << RESET << std::endl;
}
