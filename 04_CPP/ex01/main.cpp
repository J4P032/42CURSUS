/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:20:03 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/10 12:52:37 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main(void)
{
	system("clear");
	ScavTrap	a;
	ScavTrap	b("RobotB");
	ClapTrap	javi("Javier");
	a = 		ScavTrap("RobotA");

	a.attack("RobotB");
	b.takeDamage(a.getDamage());
	a.attack("RobotB");
	b.takeDamage(a.getDamage());
	b.beRepaired(50);

	b.attack("RobotA");
	a.takeDamage(b.getDamage());
	a.beRepaired(10);

	javi.beRepaired(3);
	javi.attack("Javier");
	javi.takeDamage(javi.getDamage());
	javi.beRepaired(1000);
	a.attack("Javier");
	javi.takeDamage(a.getDamage());
	javi.beRepaired(50);
	javi.attack("RobotA");

	for (size_t i = 0; i < 50; i++){
		b.guardGate();
		b.attack("RobotB");
	}
	a.beRepaired(101);
	a.attack("RobotB");
	b.beRepaired(a.getDamage());
	javi.attack("RobotB");
	for (size_t i = 0; i < 6; i++){
		a.attack("RobotB");
		b.takeDamage(a.getDamage());
	}
	a.guardGate();
	b.guardGate();
}

