/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:18:26 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/03 11:30:03 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void){
    Zombie *z;

    z = newZombie("Paco");
    z->announce();
    randomChump("Zacarias");
    delete z;
    
    Zombie *p;
    p = newZombie("");
    p->announce();
    randomChump("");
    delete p;
    
    return (0);
}
