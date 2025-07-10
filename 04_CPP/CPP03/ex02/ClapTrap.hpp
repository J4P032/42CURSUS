/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:11:56 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/10 12:50:27 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <string>
#include <iostream>
#include <cstdlib> //system("clear")

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[38;2;255;0;0m"
#define GREEN "\033[38;2;0;255;0m"
#define YELLOW "\033[38;5;226m"
#define BLUE "\033[38;2;0;100;255m"
#define MAGENTA "\033[38;2;100;50;255m"
#define CYAN "\033[38;2;0;200;255m"
#define WHITE "\033[37m"

class	ClapTrap{
	public:
		ClapTrap(void);
		ClapTrap(std::string name);
		ClapTrap(std::string name, unsigned int hitPt, unsigned int maxHitPt, unsigned int energyPt, unsigned int attackDmg);
		ClapTrap(const ClapTrap &other);
		ClapTrap &operator=(const ClapTrap &other);
		~ClapTrap(void);
	
		void			attack(const std::string &target);
		void			takeDamage(unsigned int amount);
		void			beRepaired(unsigned int amount);
		unsigned int	getDamage(void) const;
	
	protected:
		std::string		_name;
		unsigned int	_hitPt; //vida
		unsigned int	_maxHitPt;
		unsigned int	_energyPt; //para Attack o Repair
		unsigned int	_attackDmg;
};

#endif
