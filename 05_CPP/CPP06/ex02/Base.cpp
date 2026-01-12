/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:10:26 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/12 17:39:01 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::~Base(void){}

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

void	identify(Base* p){}

void 	identify(Base& p){}
