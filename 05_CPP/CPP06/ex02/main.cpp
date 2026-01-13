/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:27:40 by jrollon-          #+#    #+#             */
/*   Updated: 2026/01/13 10:57:39 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

int main(void){
	Base	*temp;
	Base	*none = NULL;
	Base	base = Base();
	
	std::srand(std::time(NULL)); //semilla para el rand()
	temp = generate();
	identify(temp);
	identify(*temp);
	if (temp)
		delete(temp); //generate alloc memoria
	
	std::cout << "----- Prueba de NULL -----" << std::endl;	
	identify(none);
	if (none) //No se puede pasar un NULL por referencia es comportamiento indefinido
		identify(*none); 
	
	std::cout << "----- Prueba de BasePadre -----" << std::endl;
	identify(&base);
	identify(base);
	
	return 0;
}
