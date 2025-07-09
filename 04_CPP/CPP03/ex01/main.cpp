/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:20:03 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/09 17:24:29 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main(void)
{
	ScavTrap	a;
	ScavTrap	b("RobotB");
	ClapTrap	javi("Javier");
	a = 	ScavTrap("RobotA");

	a.attack("RobotB");
	b.takeDamage(20);
	a.attack("RobotB");
	b.takeDamage(20);
	b.beRepaired(50);

	b.attack("RobotA");
	a.takeDamage(20);
	a.beRepaired(10);

	javi.beRepaired(3);
	javi.attack("Javier");
	javi.takeDamage(8);
	javi.beRepaired(1000);
	a.attack("Javier");
	javi.takeDamage(20);
	javi.beRepaired(50);
	
	javi.attack("RobotA");
	a.takeDamage(20);

	for (size_t i = 0; i < 50; i++){
		b.attack("RobotB");
	}
	
	a.beRepaired(101);
	a.attack("RobotB");
	b.beRepaired(200);
	javi.attack("RobotB");
	for (size_t i = 0; i < 6; i++){
		a.attack("RobotB");
		b.takeDamage(20);
	}
	
	b.beRepaired(4294967295);
	a.guardGate();
	b.guardGate();
	

}

