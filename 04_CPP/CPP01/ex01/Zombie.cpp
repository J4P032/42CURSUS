/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:19:31 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/03 11:07:49 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(void){
    std::cout << "Constructor of zombies called" << std::endl;
}
Zombie::~Zombie(void){
    std::cout << "Destructor of zombies called" << std::endl;
}

void Zombie::setName(std::string my_name)
{
    this->_name = my_name;
}

void Zombie::announce(void) const
{
    std::cout << this->_name << ": BraiiiiiiinnnzzzZ...";
    std::cout << std::endl;
}

