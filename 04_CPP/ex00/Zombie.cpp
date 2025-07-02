/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:25:18 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/02 10:58:21 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie (std::string my_name)
{
    this->_name = my_name;
}

Zombie::~Zombie (void){}

void    Zombie::announce (void) const
{
   std::cout << this->_name << ": BraiiiiiiinnnzzzZ...";
   std::cout << std::endl;
}
