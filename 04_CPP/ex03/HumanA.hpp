/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:04:07 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/02 11:00:02 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

#include "Weapon.hpp"

class	HumanA{
	public :
		HumanA(const std::string &name, Weapon &myWeapon);
		~HumanA(void);

		void	attack(void);

	private :
		std::string	_name;
		Weapon		&_myWeapon;
};

#endif
