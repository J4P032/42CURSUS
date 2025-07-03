/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:25:18 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/03 11:01:25 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie (std::string my_name)
{
    this->_name = my_name;
}

Zombie::~Zombie (void){
    std::cout << "[DEBUG] Zombie " << _name << " destroyed! See you in hell" << std::endl;
}

void    Zombie::announce (void) const
{
   std::cout << this->_name << ": BraiiiiiiinnnzzzZ...";
   std::cout << std::endl;
}
