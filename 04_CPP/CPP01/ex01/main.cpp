/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:57:49 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/03 12:01:32 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	Zombie		*horde = NULL;
	int			num_zombies = 10;
	std::string	zombie_name = "Paco";

	horde = zombieHorde(num_zombies, zombie_name);
	for (int i = 0; i < num_zombies; i++){
		horde[i].announce();
	}
		
	Zombie	*horde2 = NULL;
	horde2 = zombieHorde(0, "");
	for (int i = 0; i < 0; i++){
		horde2[i].announce();
	}
	if (horde2){
		delete[] horde2;
	}
	
	Zombie	*horde3 = NULL;
	horde3 = zombieHorde(-20, "Manolo");
	for (int i = 0; i < -20; i++){
		horde3[i].announce();
	}
	

	Zombie	*horde4 = NULL;
	horde4 = zombieHorde(1, "Manolo");
	for (int i = 0; i < 1; i++){
		horde4[i].announce();
	}
	
	if (horde){
		delete[] horde;
	}
	if (horde2){
		delete[] horde2;
	}
	if (horde3){
		delete[] horde3;
	}
	if (horde4){
		delete[] horde4;
	}
	
	return (0);
}
