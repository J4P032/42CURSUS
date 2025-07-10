/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 09:15:59 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/10 14:25:54 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include "ClapTrap.hpp"

/*DiamondTrap heredara de ScavTrap y de FragTrap. Si no le pongo virtual delante...
...a la hora de crear un objeto con DiamondTrap, se crearan dos objetos para la...
...misma ScavTrap y FragTrap haciendo que haya incongruencias. virtual hace...
...que sea solo un objeto padre, en este caso ClapTrap*/
class ScavTrap : virtual public ClapTrap{
	public:
		ScavTrap(void);
		ScavTrap(std::string name);
		ScavTrap(const ScavTrap &other);
		~ScavTrap(void);
		
		ScavTrap &operator=(const ScavTrap &other);
		
		void	attack(const std::string &target);
		void 	guardGate(void);
};

#endif
