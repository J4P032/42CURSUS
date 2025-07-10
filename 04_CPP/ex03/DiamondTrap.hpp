/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:08:59 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/10 16:20:31 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
class ClapTrap;

class DiamondTrap : public FragTrap, public ScavTrap{
	public:
		DiamondTrap(void);
		DiamondTrap(std::string name); //_clap_name
		DiamondTrap(const DiamondTrap &other);
		~DiamondTrap(void);
		
		DiamondTrap	&operator=(const DiamondTrap &other);
		std::string	getName(void) const;
		void		whoAmI();
	
	private:
		std::string	_name;
};

std::ostream &operator<<(std::ostream &out, const DiamondTrap &r);

#endif
