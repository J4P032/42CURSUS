/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:28:51 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/27 23:28:45 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie *zombieHorde(int N, std::string name)
{
    Zombie *horde;
    
    if (N <= 0)
        return (NULL);
    horde = new Zombie[N];
    for (int i = 0; i < N; i++){
        horde[i].setName(name);
    }
	return (horde);
}