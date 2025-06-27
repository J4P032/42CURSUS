/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:57:49 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/27 23:29:50 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
    Zombie  	*horde;
    int     	num_zombies = 10;
    std::string	zombie_name = "Paco";

    horde = zombieHorde(num_zombies, zombie_name);
    for (int i = 0; i < num_zombies; i++)
		horde[i].announce();
    delete[] horde;
    return (0);
}