/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:20:03 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/10 19:22:38 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

int main(void)
{
	system("clear");
	DiamondTrap	d1;
	DiamondTrap d2("Manolo");
	DiamondTrap d3;
	std::cout << d1 << std::endl;
	std::cout << d2 << std::endl;
	d3 = d2;
	std::cout << d3 << std::endl;
	DiamondTrap d4(DiamondTrap("Paco"));
	std::cout << d4 << std::endl;
	d1.whoAmI();
	d2.whoAmI();
	d3.whoAmI();
	d4.whoAmI();
	std::cout << "FIGHT!!" << std::endl;

	d1.attack("Manolo");
	d2.attack("pepito");
	d2.takeDamage(d1.getDamage());
	d2.highFivesGuys();
	d2.guardGate();
	d1.attack("Manolo");
	d2.beRepaired(15);
}
