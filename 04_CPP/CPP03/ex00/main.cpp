/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:20:03 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/08 20:55:08 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

/* int	main(void){
	ClapTrap joe("Joe");
	ClapTrap foe("Foe");
	ClapTrap toe;

	toe = ClapTrap("Toe");

	joe.attack("Foe");
	foe.takeDamage(2);

	foe.beRepaired(10);

	toe.attack("Joe");
	joe.takeDamage(4);

	
	joe.attack("Toe");
	toe.takeDamage(2);

	foe.attack("Joe");
	joe.takeDamage(3);
} */

int	main(void){
	ClapTrap paco("Paco");
	ClapTrap javi("Javi");
	ClapTrap dani;

	dani = ClapTrap("Dani");

	paco.attack("Dani");
	dani.takeDamage(3);
	javi.attack("Dani");//9
	dani.takeDamage(1);
	javi.attack("Dani");//8
	dani.takeDamage(1);
	javi.attack("Dani");//7
	dani.takeDamage(1);
	javi.attack("Dani");//6
	dani.takeDamage(1);
	javi.attack("Dani");//5
	dani.takeDamage(1);
	javi.attack("Dani");//4
	dani.takeDamage(1);
	javi.attack("Dani");//3
	dani.takeDamage(1);
	javi.attack("Dani");//2
	dani.takeDamage(1);
	
	dani.beRepaired(100);
	
	javi.attack("Paco");//1
	paco.takeDamage(6);
	javi.attack("Paco");//0
	paco.takeDamage(2);
	
	javi.attack("Paco");//0
	paco.beRepaired(4);
	paco.attack("Javi");
	javi.takeDamage(1000);
}
