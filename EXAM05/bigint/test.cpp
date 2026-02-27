/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:11:00 by jrollon-          #+#    #+#             */
/*   Updated: 2026/02/27 12:47:43 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"

int	main(void){
	bigint a(999);
	bigint b(9);
	bigint c;

	a = a + b;
	
	std::cout << a << std::endl;
	
	bigint d(999);
	if (d == a)
		std::cout << "son iguales" << std::endl;
	else
		std::cout << "son distintos" << std::endl;
	
	d = d << 5;
	std::cout << d << std::endl; 
	
	
	return 0;
}
