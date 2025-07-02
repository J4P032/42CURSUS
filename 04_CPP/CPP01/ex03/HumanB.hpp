/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:04:46 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/02 11:00:21 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

#include "Weapon.hpp"

class	HumanB{
	public :
		HumanB(const std::string &name);
		~HumanB(void);

		void	attack(void);
		void	setWeapon(Weapon &weapon);

	private :
		std::string	_name;
		Weapon		*_myWeapon;
};

#endif
