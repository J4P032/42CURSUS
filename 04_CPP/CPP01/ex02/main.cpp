/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:31:27 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/01 14:45:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(void)
{
	std::string	var1 = "HI THIS IS BRAIN";
	std::string	*stringPTR = &var1;
	std::string	&stringREF = var1;

	std::cout << "address of string:\t\t" << &var1 << std::endl;
	std::cout << "address held by stringPTR:\t" << stringPTR << std::endl;
	std::cout << "address held by stringREF:\t" << &stringREF << std::endl;
	std::cout << "value of string var:\t\t" << var1 << std::endl;
	std::cout << "value pointed by stringPTR:\t" << *stringPTR << std::endl;
	std::cout << "value pointed by stringREF:\t" << stringREF << std::endl;
	
	return (0);
}
