/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:25:18 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/26 11:29:20 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie (std::string my_name)
{
    this->name = my_name;
}

Zombie::~Zombie (void){}

void    Zombie::announce (void) const
{
   std::cout << this->name << ": BraiiiiiiinnnzzzZ...";
   std::cout << std::endl;
}
